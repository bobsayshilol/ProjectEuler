/**
 * Special Pythagorean triplet
 * 
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
 * a^2 + b^2 = c^2
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 * Find the product abc.
 */

/**
 * a^2 + b^2 = c^2 = (a + b - 1000)^2 = a^2 + b^2 + 2ab + 1000000 - 2000(a + b)
 * => 1000(a + b) = ab + 500000
 * => abc = (1000 - a - b)(1000(a + b) - 500000)
 * 
 * Also b < 500, since b >= 500 => c > b >= 500 => a + b + c >= a + 500 + 500 = a + 1000 > 1000
 * 
 * So we are looking for a solution to ab - 1000(a + b) + 500000 = 0 with a < b < 500
 * Note that there is probably some optimisation that can be done by treating ^ as a continuous function
 * and guessing a first approximation.
 * 
 * (x-a)(x-b) = x^2 - x(a+b) + ab, but 1000^2 != 500000, so that's of no use
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(9, uint64_t)
{
	// Loop within a loop to look for the right values
	for (uint64_t b=1; b<500; b++)
	{
		for (uint64_t a=1; a<b; a++)
		{
			if (a*b - 1000 * (a + b) + 500000 == 0)
			{
				// Calculate abc
				result = (1000 - a - b) * (1000 * (a + b) - 500000);
			}
		}
	}
}
SOLUTION_END()
