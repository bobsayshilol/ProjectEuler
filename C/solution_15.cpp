/**
 * Lattice paths
 * 
 * Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
 * How many such routes are there through a 20×20 grid?
 */

/**
 * Simple combinations.
 * Since we are only dealing with right and down we can't go back on ourselves, so there are always going to be a total of width + height moves.
 * Then we have 20 min(height, width) choices to make.
 * So the answer is nCk, where n = width + height, k = min(width, height)
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(15, uint64_t)
{
	// The size of the board
	constexpr uint64_t width = 20;
	constexpr uint64_t height = 20;
	
	// Calculate (width + height) choose min(width, height)
	constexpr uint64_t N = width + height;
	constexpr uint64_t k = (width > height) ? width : height;
	constexpr uint64_t Nk = N - k + 1;
	
	// Since we're dealing with values that overflow a uint64_t even when considering the numerator and denominator separately, it looks
	// like we'll have to do some fancy tricks here instead.
	
	// Initialise the result as we'll continually multiply and divide this
	result = 1;
	
	// In order to get the right result we need to multiply "result" by all the numbers between "N" and "Nk" and divide it by all numbers <= k.
	// This is used to keep track of which numbers we have yet to divide into "result"
	std::vector<uint8_t> divisors(k + 1, 0);
	
	// Go through all numbers between "N" and "Nk"
	for (uint64_t i=Nk; i<=N; i++)
	{
		// Multiply it
		result *= i;
		
		// Check for any divisors we can knock off our list
		for (uint64_t div=1; div <= k; div++)
		{
			// If it's divisible and we haven't set it yet then divide it
			if ((divisors[div] == 0) && ((result % div) == 0))
			{
				result /= div;
				divisors[div] = 1;
			}
		}
	}
}
SOLUTION_END()
