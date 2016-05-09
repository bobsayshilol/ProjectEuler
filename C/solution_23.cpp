/**
 * Non-abundant sums
 * 
 * A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
 * A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.
 * Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
 */

/**
 * TL;DR:
 * perfect number if sum of proper divisors = original number
 * deficient number if sum < n
 * abundant if sum > n
 * 
 * 12 is smallest abundant (sum = 16)
 * => 24 = smallest sum of two abundant numbers
 * 
 * we're given that 28123 is largest possible
 * 
 * Let x have proper divisor sum s and prime decomposition product(p^k_p, p E primes)
 * Then s = product((p^(k_p+1) - 1)/(p-1), p E primes) - x (from problem 21)
 * 
 * Let y = a + b, where a and b are abundant numbers
 * Then the solution is sum(i) - sum(y)
 * 
 * 
 * 
 * Brute force it
 */



// Common includes
#include "common.h"



// Function to calculate the proper divisors and sum them
static uint64_t GetProperDivisorSum(const std::vector<uint64_t>& primes, const uint64_t composite)
{
	uint64_t sum = 1;
	
	// Get the prime factors of composite
	uint64_t compositeTemp = composite;
	for (uint64_t prime : primes)
	{
		// See how many times the currently decomposed value is divisible by this prime
		uint64_t primeCount = 0;
		while ((compositeTemp % prime) == 0)
		{
			primeCount++;
			compositeTemp /= prime;
		}
		
		// Don't do the calculation if this prime isn't a factor
		if (primeCount == 0)
			continue;
		
		// Calculate the power sum for this prime
		// sum(p^i, i=0..k_p) = (p^(k_p+1) - 1) / (p - 1)
		const uint64_t powerSum = (std::pow(prime, primeCount+1) - 1) / (prime - 1);
		
		// Multiply the current sum by the sum of the powers
		sum *= powerSum;
		
		// If there's no more possible factors then break out of the loop
		if (compositeTemp == 1)
			break;
	}
	
	// The sum doesn't want the actual composite number
	sum -= composite;
	
	return sum;
}



// Begin the solution
SOLUTION_BEGIN(23, uint64_t)
{
	// Max value
	const uint64_t max = 28123;
	
	// Get the largest value the sieve needs
	// TODO: can this be optimised? can't tell
	const uint64_t maxPrime = max;
	
	// Make a sieve up to maxPrime, ignoring 0
	// Use a uint8_t rather than a bool since the bool specialisation is slooooow
	std::vector<uint8_t> sieve(maxPrime+1, 1);
	
	// And another vector for all the primes
	std::vector<uint64_t> primes;
	primes.reserve(maxPrime);
	
	// Special case 2
	primes.push_back(2);
	
	// Create the sieve
	for (uint64_t prime=3; prime<=maxPrime; prime+=2)
	{
		// If this value hasn't been set then it must be prime
		if (sieve[prime] == 1)
		{
			// Go through all multiples of prime and set them to false in the sieve
			for (uint64_t multiple=prime*prime; multiple<=maxPrime; multiple+=2*prime)
			{
				sieve[multiple] = 0;
			}
			
			// Add the prime to the list
			primes.push_back(prime);
		}
	}
	
	// Initialise the result
	result = 0;
	
	// Create a list of abundant numbers as we go
	std::vector<uint64_t> abundants;
	abundants.reserve(max);
	for (uint64_t n=1; n<max; n++)
	{
		// Check if it's abundant
		if (GetProperDivisorSum(primes, n) > n)
		{
			abundants.push_back(n);
		}
		
		// Then brute force check if we can be decomposed into 2 abundants
		bool decomposed = false;
		const size_t abundantCount = abundants.size();
		for (size_t i=0; i<abundantCount && !decomposed; i++)
		{
			bool triedOnce = false;
			const uint64_t abundant1 = abundants[i];
			
			// We start from the reverse since as n increases we expect it to be more likely to be abundant
			for (ssize_t j=abundantCount-1; j>=0 && !decomposed; j--)
			{
				const uint64_t abundant2 = abundants[j];
				
				// Check if it decomposed
				if (abundant1 + abundant2 == n)
					decomposed = true;
				
				// No point checking any more if this is too small
				if (abundant1 + abundant2 <= n)
					break;
				
				triedOnce = true;
			}
			
			// If we failed the first attempt then there's no point in carrying on since we know this number
			// can't be decomposed into two that don't sum to make it
			if (!triedOnce)
				break;
		}
		
		// Add it to the sum
		if (!decomposed)
		{
			result += n;
		}
	}
}
SOLUTION_END()
