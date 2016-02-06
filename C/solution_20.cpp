/**
 * Factorial digit sum
 * 
 * n! means n × (n − 1) × ... × 3 × 2 × 1
 * For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
 * and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 * Find the sum of the digits in the number 100!
 */

/**
 * Modified copy of solution to problem 16
 * 
 * Let k! = sum(a_i(k) * 10^i, i=0..N)
 * st k! < 10^(N+1)
 * => N + 1 > log(k!) / log(10)
 * 
 * k! = k * (k-1) * (k-2) * ... 3 * 2 * 1 < k * k * k * ... * k * k * k = k^k
 * => log(k!) / log(10) < k * log(k) / log(10)
 * So let N = k * log(k) / log(10)
 * 
 * 9!  =  362880
 * 10! = 3628800
 * 
 * Let B = ... + b_i * 10^i + b_(i-1) * 10^(i-1) + ...
 * then m * B = ... + m * b_i * 10^i + m * b_(i-1) * 10^(i-1) + ... = ... + c_i * 10^i + c_(i-1) * 10^(i-1) + ...
 * => c_i = m * b_i + m * b_(i-1) / 10 + ... = sum(m * b_(i-p) / 10^p, p=0..i)
 * Let q be st m * b_(i-q) < 10^q for all i
 * max(b_i) <= 9
 * => m * b_(i-q) <= 9 * m
 * So we can pick q st 9 * m < 10^q
 * => q > log(9 * m) / log(10) = log(9)/log(10) + log(m)/log(10)
 * So q = log(m)/log(10) + 1
 * 
 * So only the last "q" digits effect the result of multiplying by m if we ignore the parts after the decimal place
 * Since m <= k, we can pick q = log(k)/log(10) + 1
 * 
 * Since we're ignoring the bit after the decimal place in the above calculation, we'd need to double q to take them
 * into account
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(20, uint64_t)
{
	// k as above
	constexpr uint64_t k = 100;
	
	// Calculate N
	constexpr uint64_t N = (k * log(k)) / log(10);
	
	// Calculate q
	constexpr size_t q = 2 * (log(k) / log(10) + 1);
	
	// Create two buffers of length "N" + 1 to do the recursion in
	uint8_t buffers[2][N + 1] = { 0 };
	
	// Initialise the first buffer to 1
	buffers[0][0] = 1;
	
	// Recurse
	size_t currentBuffer = 0;
	for (size_t i=1; i<=k; i++)
	{
		// Simple swap to get the next buffer
		const size_t nextBuffer = 1 - currentBuffer;
		
		// Go through each digit and apply the equations above
		const uint8_t * cbuffer = buffers[currentBuffer];
		uint8_t * nbuffer = buffers[nextBuffer];
		
		// 0 is a special case
		nbuffer[0] = (cbuffer[0] * i) % 10;
		
		for (size_t j=1; j<=N; j++)
		{
			// What the value of this digit will be
			uint64_t digitSum = 0;
			
			// Make sure we don't index past the array
			const size_t finalDigitPosition = std::min(q, j);
			
			// Deal with up to the last "q" digits
			for (size_t p=0; p<=finalDigitPosition; p++)
			{
				// Note that because we're dealing with whole numbers we
				// need to factor out the 1/10^p bit otherwise everything
				// comes out as 0
				digitSum += (cbuffer[j - p] * i) * std::pow(10, finalDigitPosition-p);
			}
			
			// Do the division bit from the factored out 10
			digitSum /= std::pow(10, finalDigitPosition);
			
			// Make sure it's between 0 and 9
			nbuffer[j] = digitSum % 10;
		}
		
		/*
		printf("cbuffer=");
		for (ssize_t j=N; j>=0; j--)
			printf("%" PRIu8, cbuffer[j]);
		printf(", nbuffer=");
		for (ssize_t j=N; j>=0; j--)
			printf("%" PRIu8, nbuffer[j]);
		printf("\n");
		*/
		
		// Swap the buffers
		currentBuffer = nextBuffer;
	}
	
	// Initialise the result
	result = 0;
	
	// The last buffer now contains the digits, so sum them
	uint8_t * buffer = buffers[currentBuffer];
	for (size_t i=0; i<=N; i++)
	{
		result += buffer[i];
	}
}
SOLUTION_END()
