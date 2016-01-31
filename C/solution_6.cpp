/**
 * Sum square difference
 * 
 * The sum of the squares of the first ten natural numbers is,
 * 1^2 + 2^2 + ... + 10^2 = 385
 * The square of the sum of the first ten natural numbers is,
 * (1 + 2 + ... + 10)^2 = 55^2 = 3025
 * Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
 * Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
 */

/**
 * sum(i, i=1..N) = N * (N + 1) / 2
 * sum(i^2, i=1..N) = N * (2*N + 1) * (N + 1) / 6
 * => sum(i, i=1..N)^2 - sum(i^2, i=1..N) = (N * (N + 1) / 2)^2 - N * (2*N + 1) * (N + 1) / 6
 *       = N * (N + 1) * ( 3 * N * (N + 1) - 4*N - 2 ) / 12 = N * (N + 1) * ( 3 * N^2 - N - 2 ) / 12
 * 
 * Simple
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(6, uint64_t)
{
	// The maximum number
	const uint64_t N = 100;
	
	// Calculate the result
	result = (N * (N + 1) * ( 3 * N * N - N - 2 )) / 12;
}
SOLUTION_END()
