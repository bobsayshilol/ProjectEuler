/**
 * Highly divisible triangular number
 * 
 * The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
 * 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
 * Let us list the factors of the first seven triangle numbers:
 *     1: 1
 *     3: 1,3
 *     6: 1,2,3,6
 *    10: 1,2,5,10
 *    15: 1,3,5,15
 *    21: 1,3,7,21
 *    28: 1,2,4,7,14,28
 * We can see that 28 is the first triangle number to have over five divisors.
 * What is the value of the first triangle number to have over five hundred divisors?
 */

/**
 * let T(n) be the nth triangle number, then T(n) = n * (n + 1) / 2
 * 
 *     28
 *    /  \
 *   2   14
 *      /  \
 *     2    7
 *         / \
 *        7   1
 * 1,2,2,7 -> 1,2,4,7,14,28 = 6 = (2+1)(1+1)
 * 
 * Let N be any number, then factoring N gives N = product(p^(p_i), p prime), and the number of factors are given by product(p_i+1)
 * 
 * So it's time to make another sieve.
 * For the limit of the sieve we can use n+1, since the largest factor of T(n) is at most n+1.
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(12, uint64_t)
{
	// The number of divisors to look for
	const uint64_t divisors = 500;
	
	// Since the sieve requires us knowing how big the end result is we need to make
	// it adaptive. For this we set a chunk size, and when we encounter a number
	// larger than it we extend the size of the sieve by another chunk and re-run
	// the algorithm on it.
	const uint64_t chunkSize = 128 * 1024;	// 128KB
	
	// Make a vector for the sieve
	// Use a uint8_t rather than a bool since the bool specialisation is slooooow
	std::vector<uint8_t> sieve;
	
	// And another vector for all the primes
	std::vector<uint64_t> primes;
	
	// Function to populate the sieve
	uint64_t chunks = 0;
	auto UpdateSieve = [&](uint64_t max)
	{
		// See if we already have a large enough sieve
		if (max < chunks * chunkSize)
			return;
		
		// Otherwise we need to increase the size of the sieve
		chunks = max / chunkSize + 1;
		
		// Resize the sieve and the primes
		sieve.clear();
		sieve.resize(chunks * chunkSize, 1);
		primes.clear();
		primes.reserve(chunks * chunkSize / 2);	// only allocate the storage
		
		// Special case 2
		primes.push_back(2);
		
		// Start at 3
		uint64_t prime = 3;
		while (prime < chunks * chunkSize)
		{
			// If this value hasn't been set then it must be prime
			if (sieve[prime] == 1)
			{
				// Go through all multiples of prime and set them to false in the sieve
				for (uint64_t multiple=prime*prime; multiple<chunks*chunkSize; multiple+=2*prime)
				{
					sieve[multiple] = 0;
				}
				
				// Add the prime to the list
				primes.push_back(prime);
			}
			
			// Move to the next odd number
			prime += 2;
		}
	};
	
	// Go through each triangle number
	uint64_t i=0;
	while (++i)
	{
		// Calculate the triangle number
		const uint64_t tri = i * (i + 1) / 2;
		
		// Update the sieve
		UpdateSieve(i+1);
		
		// Get the prime factors of tri
		uint64_t triTemp = tri;
		uint64_t factorCount = 1;
		for (uint64_t prime : primes)
		{
			// See how many times the currently decomposed value is divisible by this prime
			uint64_t primeCount = 0;
			while ((triTemp % prime) == 0)
			{
				primeCount++;
				triTemp /= prime;
			}
			
			// Multiply that count with the current factor count
			factorCount *= primeCount + 1;
			
			// If there's no more possible factors then break out of the loop
			if (triTemp == 1)
				break;
		}
		
		// See if this triangle number has enough factors
		if (factorCount > divisors)
		{
			result = tri;
			break;
		}
	}
}
SOLUTION_END()
