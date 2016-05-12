/**
 * Number spiral diagonals
 * 
 * Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
 * 21 22 23 24 25
 * 20  7  8  9 10
 * 19  6  1  2 11
 * 18  5  4  3 12
 * 17 16 15 14 13
 * It can be verified that the sum of the numbers on the diagonals is 101.
 * What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
 */

/**
 * Spot the pattern:
 * (1)  1  = 1                   = 1
 * (2)  3  = 1 + 1*2             = 1 + 1*2  = 1 + 2(n-1)
 * (3)  5  = 1 + 2*2             = 1 + 2*2
 * (4)  6  = 1 + 3*2             = 1 + 3*2
 * (5)  9  = 1 + 4*2             = 1 + 4*2
 * (6)  13 = 1 + 5*2 + 1*2       = 1 + 6*2  = 1 + 2(n-1 + n-5)
 * (7)  17 = 1 + 6*2 + 2*2       = 1 + 8*2
 * (8)  21 = 1 + 7*2 + 3*2       = 1 + 10*2
 * (9)  25 = 1 + 8*2 + 4*2       = 1 + 12*2
 * (10) 31 = 1 + 9*2 + 5*2 + 1*2 = 1 + 15*2 = 1 + 2(n-1 + n-5 + n-9)
 * 
 * S(n) = 1 + 2[n-1] + 2[n-5] + 2[n-9] + 2[n-13] + ...
 * Where [x] = { x, x >=0; 0, otherwise }
 * 
 * 1001x1001 square => 2001 numbers to sum (ignoring the center number we have an X that can be condensed to 2 lines, each 1000 numbers long)
 * 
 * Simple set of sums
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(28, uint64_t)
{
	// Width of the square
	const uint64_t squareSize = 1001;
	
	
	// The total number of numbers to sum
	const uint64_t numbers = 2 * squareSize - 1;
	
	// The number of concentric circles to sum
	const uint64_t circles = (squareSize - 1) / 2;
	
	// Initialise the result to the sum of the ones
	result = numbers;
	
	// Go through each circle adding on the sums that start at it
	for (uint64_t i=0; i<circles; i++)
	{
		// Get the number of numbers left
		const uint64_t numbersLeft = numbers - 4*i - 1;
		
		// Calculate the sum for this ring
		const uint64_t sum = (numbersLeft * (numbersLeft + 1));
		
		result += sum;
	}
}
SOLUTION_END()
