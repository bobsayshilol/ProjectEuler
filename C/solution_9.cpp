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
 * 
 * Solving for a gives
 * a = 1000 * (500 - b) / (1000 - b)
 * and similarly for b
 * b = 1000 * (500 - a) / (1000 - a)
 * 
 * So we are looking for an integer b < 500 st 1000 * (500 - b) is divisible by (1000 - b)
 * 
 * 
 * (x-a)(x-b) = x^2 - x(a+b) + ab, but 1000^2 != 500000, so that's of no use
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(9, uint64_t)
{
	// Go through the numbers as described above
	for (uint64_t b=1; b<500; b++)
	{
		// Calculate the numerator and denominator
		const uint64_t a_numerator = 500000 - 1000 * b;
		const uint64_t a_denominator = 1000 - b;
		
		// See if it's divisible
		if ( (a_numerator % a_denominator) == 0 )
		{
			// Calculate a
			uint64_t a = a_numerator / a_denominator;
			
			// Calculate abc = (1000 - a - b)(1000(a + b) - 500000)
			result = (1000 - a - b) * (1000 * (a + b) - 500000);
			
			// Finished
			break;
		}
	}
}
SOLUTION_END()
