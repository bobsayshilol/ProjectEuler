/**
 * Largest prime factor
 * 
 * The prime factors of 13195 are 5, 7, 13 and 29.
 * What is the largest prime factor of the number 600851475143 ?
 */

/**
 * Brute force up to sqrt(N) by creating a sieve first
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(3, uint64_t)
{
	// The composite number
	const uint64_t N = 600851475143;
	
	// Get the largest value it could be
	const uint64_t sqrtN = sqrt(N);
	
	// Make a sieve up to sqrtN, ignoring 0
	std::vector<bool> sieve(sqrtN+1, true);
	
	// Create the sieve
	for (uint64_t prime=2; prime<=sqrtN; prime++)
	{
		// If this value hasn't been set then it must be prime
		if (sieve[prime])
		{
			// Go through all multiples of prime and set them to false in the sieve
			for (uint64_t multiple=2*prime; multiple<=sqrtN; multiple+=prime)
			{
				sieve[multiple] = false;
			}
			
			// Since prime can only be increasing, we can get the result here
			if ((N % prime) == 0)
			{
				result = prime;
			}
		}
	}
	
}
SOLUTION_END()
