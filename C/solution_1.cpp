/**
 * Multiples of 3 and 5:
 * 
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */

/**
 * (Sum of multiples of 3 or 5) = (sum of multiples of 3) + (sum of multiples of 5) - (sum of multiples of 15 (3*5))
 * 
 * sum of multiples of x from i=1..N = sum(i*x, i=1..floor(N/x)) = x * sum(i, i=1..floor(N/x)) = x * floor(N/x) * (floor(N/x)+1) / 2
 * 
 * => (Sum of multiples of 3 or 5 from i=1..N)
 *     = (sum of multiples of 3 from i=1..N) + (sum of multiples of 5 from i=1..N) - (sum of multiples of 15 (3*5) from i=1..N)
 *     = 3 * floor(N/3) * (floor(N/3)+1) / 2 + 5 * floor(N/5) * (floor(N/5)+1) / 2 - 15 * floor(N/15) * (floor(N/15)+1) / 2
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(1, uint64_t)
{
	// The calculation above uses the sum to N, so we need to use N-1 here
	uint64_t N = 1000 - 1;
	
	// floor(N/3)
	uint64_t floorN3 = N / 3;
	// floor(N/5)
	uint64_t floorN5 = N / 5;
	// floor(N/15)
	uint64_t floorN15 = N / 15;
	
	// Add each part to the result
	result  = (3  * floorN3  * (floorN3  + 1)) / 2;
	result += (5  * floorN5  * (floorN5  + 1)) / 2;
	result -= (15 * floorN15 * (floorN15 + 1)) / 2;
	
}
SOLUTION_END()
