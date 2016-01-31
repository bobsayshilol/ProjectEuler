/**
 * Summation of primes
 * 
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 * Find the sum of all the primes below two million.
 */

/**
 * More sieving
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(10, uint64_t)
{
	// The largest number
	const uint64_t N = 2000000;
	
	// Make sure the result is 0 to start with
	result = 0;
	
	// Make a sieve up to N, ignoring 0
	// Use a uint8_t rather than a bool since the bool specialisation is slooooow
	std::vector<uint8_t> sieve(N, 1);
	
	// Create the sieve
	for (uint64_t prime=2; prime<N; prime++)
	{
		// If this value hasn't been set then it must be prime
		if (sieve[prime] == 1)
		{
			// Go through all multiples of prime and set them to false in the sieve
			for (uint64_t multiple=2*prime; multiple<N; multiple+=prime)
			{
				sieve[multiple] = 0;
			}
			
			// Add to the result
			result += prime;
		}
	}
}
SOLUTION_END()
