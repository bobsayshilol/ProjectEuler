/**
 * Power digit sum
 * 
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 * What is the sum of the digits of the number 2^1000?
 */

/**
 * Let 2^k = sum(a_i(k) * 10^i, i=0..N)
 * st 2^k < 10^(N+1
 * => N + 1 > k * log(2) / log(10)
 * So N = k * log(2) / log(10)
 * 
 * 2^15 = 32768
 * 2^16 = 65536
 * 
 * a_i(k+1) = a_i(k) * 2 + (a_(i-1)(k) >= 5) ? 1 : 0 (mod 10)
 * 
 * So we can recurse from 2^0 = 1 up to 1000
 * 
 * Note that this is easily extensible to M^k
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(16, uint64_t)
{
	// k as above
	constexpr uint64_t k = 1000;
	
	// Calculate N
	constexpr uint64_t N = (k * log(2)) / log(10);
	
	// Create two buffers of length "N" + 1 to do the recursion in
	uint8_t buffers[2][N + 1] = { 0 };
	
	// Initialise the first buffer to 1
	buffers[0][0] = 1;
	
	// Recurse
	size_t currentBuffer = 0;
	for (size_t i=0; i<k; i++)
	{
		// Simple swap to get the next buffer
		const size_t nextBuffer = 1 - currentBuffer;
		
		// Go through each digit and apply the equations above
		const uint8_t * cbuffer = buffers[currentBuffer];
		uint8_t * nbuffer = buffers[nextBuffer];
		
		// 0 is a special case
		nbuffer[0] = (cbuffer[0] * 2) % 10;
		
		for (size_t j=1; j<=N; j++)
		{
			// a_i(k+1) = a_i(k) * 2 + (a_(i-1)(k) >= 5) ? 1 : 0
			nbuffer[j] = (cbuffer[j] * 2 + ((cbuffer[j-1] >= 5) ? 1 : 0)) % 10;
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
