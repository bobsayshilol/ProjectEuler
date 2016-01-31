/**
 * Largest palindrome product
 * 
 * A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
 * Find the largest palindrome made from the product of two 3-digit numbers.
 */

/**
 * Let M = A * B, where
 *   A = 100 * A2 + 10 * A1 + 1 * A0,
 *   B = 100 * B2 + 10 * B1 + 1 * B0,
 *   M = 100000 * M5 + 10000 * M4 + 1000 * M3 + 100 * M2 + 10 * M1 + 1 * M0
 * Since M is a palindrome, M5 = M0, M4 = M1, M3 = M2
 * 
 * Assuming M5 = 9
 *   => M0 = 9
 * Therefore both A and B must be odd numbers
 * 
 * Brute force time?
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(4, uint64_t)
{
	// Brute force through all 9XX numbers
	for (int64_t A1=9; A1>=0; A1--)
	{
		// Since A is odd we can take away 2 at a time
		for (int64_t A0=9; A0>=0; A0-=2)
		{
			// Cache A
			uint64_t A = 900 + 10 * A1 + A0;
			
			// We can start at A rather than 999 since otherwise we'd be doing the same calculation twice
			// ie 999 * 998 = 998 * 999
			for (int64_t B1=A1; B1>=0; B1--)
			{
				// Since B is odd we can take away 2 at a time
				for (int64_t B0=A0; B0>=0; B0-=2)
				{
					// Get B
					uint64_t B = 900 + 10 * B1 + B0;
					
					// Calculate M
					const uint64_t M = A * B;
					
					// See if it's palindromic
					uint64_t M0 = M % 10;
					uint64_t M1 = ((M - M0)/10) % 10;
					uint64_t M2 = ((((M - M0)/10) - M1)/10) % 10;
					uint64_t M3 = ((((((M - M0)/10) - M1)/10) - M2)/10) % 10;
					uint64_t M4 = ((((((((M - M0)/10) - M1)/10) - M2)/10) - M3)/10) % 10;
					uint64_t M5 = ((((((((((M - M0)/10) - M1)/10) - M2)/10) - M3)/10) - M4)/10) % 10;
					if (M5 == M0 && M4 == M1 && M3 == M2)
					{
						result = M;
						// yes, it's a goto
						goto finished;
					}
				}
			}
		}
	}
	
finished:
	// This line is needed for GCC to compile
	result = result;
}
SOLUTION_END()
