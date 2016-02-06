/**
 * Amicable numbers
 * 
 * Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
 * If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
 * For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
 * Evaluate the sum of all the amicable numbers under 10000.
 */

/**
 * d(a) = b and d(b) = a => a + b = a + d(a)
 * let a < b, then for all a we only need to check if d(d(a)) = a when d(a) > a
 * Note that this also lets us check for numbers where a < 10000 but d(a) > 10000
 * 
 * Plus we need a sieve
 * 
 * It looks like we may be able to sum these:
 * 6 = 2 * 3
 * 6 -> 1, 2, 3, 6 = 12
 * 1 + 2 + 3 + 2*3 = (1+2)(1+3) = 12
 * 
 * Quick check
 * M = a * b
 * => sum = 1 + a + b + ab = (1+a)(1+b)
 * M = a * b * c
 * => sum = 1 + a + b + c + ab + bc + ac + abc = (1+a)(1+b)(1+c)
 * M = a * a
 * => sum = 1 + a + aa = (1+a+aa)
 * M = a * b * b
 * => sum = 1 + a + b + ab + bb + abb = (1+a)(1+b+bb)
 * 
 * Let M = product(p^k_p, p prime)
 * Then the sum = product(sum(p^i, i=0..k_p))
 * sum(p^i, i=0..k_p) = (p^(k_p+1) - 1) / (p - 1)
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(21, uint64_t)
{
	// Maximum value
	const uint64_t max = 10000;
	
	// Get the largest value the sieve needs
	// TODO: can this be optimised? can't tell
	const uint64_t maxPrime = max;
	
	// Make a sieve up to maxPrime, ignoring 0
	// Use a uint8_t rather than a bool since the bool specialisation is slooooow
	std::vector<uint8_t> sieve(maxPrime+1, 1);
	
	// And another vector for all the primes
	std::vector<uint64_t> primes;
	primes.reserve(maxPrime);
	
	// Create the sieve
	for (uint64_t prime=2; prime<=maxPrime; prime++)
	{
		// If this value hasn't been set then it must be prime
		if (sieve[prime] == 1)
		{
			// Go through all multiples of prime and set them to false in the sieve
			for (uint64_t multiple=2*prime; multiple<=maxPrime; multiple+=prime)
			{
				sieve[multiple] = 0;
			}
			
			// Add the prime to the list
			primes.push_back(prime);
		}
	}
	
	// Function to calculate the proper divisors and sum them
	auto GetProperDivisorSum = [&primes](const uint64_t composite)
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
	};
	
	// Initialise the result
	result = 0;
	
	// Go through each value looking for pairs
	for (uint64_t a=2; a < max; a++)
	{
		// If this is prime then skip it
		if (sieve[a] == 1)
			continue;
		
		// Otherwise calculate the proper divisor sum
		const uint64_t sum = GetProperDivisorSum(a);
		
		// Apply the logic above
		if (sum > a)
		{
			if (GetProperDivisorSum(sum) == a)
			{
				// If it passed then b = sum
				result += sum + a;
			}
		}
	}
}
SOLUTION_END()
