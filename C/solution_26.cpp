/**
 * Reciprocal cycles
 * 
 * A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:
 *    1/2	= 	0.5
 *    1/3	= 	0.(3)
 *    1/4	= 	0.25
 *    1/5	= 	0.2
 *    1/6	= 	0.1(6)
 *    1/7	= 	0.(142857)
 *    1/8	= 	0.125
 *    1/9	= 	0.(1)
 *    1/10	= 	0.1 
 * Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
 * Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
 */

/**
 * Something to do with modular arithmetic...
 * 
 * 0.142857
 * ________________
 * 1.0 <-------\
 * 0.7         |
 * ----        |
 * 0.30        |
 * 0.28        |
 * -----       |
 * 0.020       |
 * 0.014       |
 * ------      |
 * 0.0060      |
 * 0.0056      |
 * -------     |
 * 0.00040     |
 * 0.00035     |
 * --------    |
 * 0.000050    |
 * 0.000049    |
 * ---------   |
 * 0.0000010 --/
 * 
 * r = 142857
 * d = 7
 * 10^k = 1000000
 * 
 * 10^k % d = 1
 * 
 * 10^k = 1 (mod d)
 * 
 * 10^k = ((10-d) + d)^k = (10-d)^k (mod d)
 * 
 * Note that by the pigeonhole principle if we see the same number twice we're back at the start
 * 
 * Simple algorithm:
 * Calculate 10^k (mod d) for increasing values of k
 * if 10^k = 0 (mod d) then not repeating
 * if 10^k = L (mod d) then it repeats with |k-l| digits, where 10^l = L (mod d)
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(26, uint64_t)
{
	// Largest value of d
	const uint64_t max = 1000;
	
	
	// Initialise the result
	result = 0;
	
	// Array for keeping track of when we saw different remainders
	std::vector<int64_t> remainders;
	
	// Keep track of the longest cycle
	uint64_t longestCycle = 0;
	
	// Go through each number
	for (uint64_t d=1; d<max; d++)
	{
		// Initialise the variables as above
		uint64_t k = 1;
		uint64_t remainder = 10;
		remainders.clear();
		remainders.resize(max, -1);
		
		// We always see 1 first (1/d)
		remainders[1] = 0;
		
		do
		{
			// Do the modulo
			remainder %= d;
			
			// This decimal terminates
			if (remainder == 0)
				break;
			
			// Check if we've seen this remainder before
			int64_t& lastSeen = remainders[remainder];
			if (lastSeen != -1)
			{
				const uint64_t cycle = k - lastSeen;
				if (cycle > longestCycle)
				{
					longestCycle = cycle;
					result = d;
				}
				break;
			}
			
			// Mark that we've seen this remainder
			lastSeen = k;
			
			// Move on to the next power
			remainder *= 10;
			k++;
		}
		while (true);
	}
}
SOLUTION_END()
