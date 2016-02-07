/**
 * 10001st prime
 * 
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
 * What is the 10,001st prime number?
 */

/**
 * Brute force sieve, again
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(7, uint64_t)
{
	// The prime number we want
	const uint64_t primeIndex = 10001;
	
	// Since the sieve requires us knowing how big the end result is we need to make
	// it adaptive. For this we set a chunk size, and when we encounter a number
	// larger than it we extend the size of the sieve by another chunk and re-run
	// the algorithm on it.
	const uint64_t chunkSize = 128 * 1024;	// 128KB
	uint64_t chunks = 1;
	
	// Make a vector for the sieve
	// Use a uint8_t rather than a bool since the bool specialisation is slooooow
	std::vector<uint8_t> sieve;
	
	// The current prime count
	uint64_t primeCount = 0;
	
	// Create the sieve
	bool found = false;
	do
	{
		// Reset the state
		primeCount = 0;
		sieve.clear();
		
		// Resize the sieve
		sieve.resize(chunks * chunkSize, 1);
		
		// Special case 2
		if (++primeCount == primeIndex)
		{
			result = 2;
			found = true;
		}
		
		// Start at 3
		uint64_t prime = 3;
		while ((prime < chunks * chunkSize) && !found)
		{
			// If this value hasn't been set then it must be prime
			if (sieve[prime] == 1)
			{
				// Go through all multiples of prime and set them to false in the sieve
				for (uint64_t multiple=prime*prime; multiple<chunks*chunkSize; multiple+=2*prime)
				{
					sieve[multiple] = 0;
				}
				
				// Add to the prime count and see if this is the one we want
				if (++primeCount == primeIndex)
				{
					result = prime;
					found = true;
				}
			}
			
			// Move to the next odd number
			prime += 2;
		}
		
		// Increase the number of chunks
		chunks++;
	}
	while (!found);
}
SOLUTION_END()
