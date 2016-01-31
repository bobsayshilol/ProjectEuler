/**
 * Smallest multiple
 * 
 * 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
 * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 */

/**
 * For each number between 1 and 20 we need to work out the gcd of each number with a total product, then we can
 * multiply the total product by the new number and divide it by the gcd.
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(5, uint64_t)
{
	// The maximum number
	const uint64_t max = 20;
	
	// Set to 1 initially. This is the total product mentioned above
	result = 1;
	
	// Simple function to calculate the GCD of 2 numbers
	auto GCD = [](uint64_t a, uint64_t b)
	{
		// Make sure a >= b
		if (a < b)
			std::swap(a, b);
		
		// Simple loop
		uint64_t gcd;
		while ((gcd = a % b) != 0)
		{
			a = b;
			b = gcd;
		}
		
		return b;
	};
	
	// Go through each number in the list
	for (uint64_t i=1; i<max; i++)
	{
		// Calculate the gcd
		uint64_t gcd = GCD(i, result);
		
		// Since the gcd divides both i and result fully we don't need to bother with bracket ordering
		result = result * i / gcd;
	}
}
SOLUTION_END()
