/**
 * Longest Collatz sequence
 * 
 * The following iterative sequence is defined for the set of positive integers:
 * n → n/2 (n is even)
 * n → 3n + 1 (n is odd)
 * Using the rule above and starting with 13, we generate the following sequence:
 * 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
 * It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
 * Which starting number, under one million, produces the longest chain?
 * NOTE: Once the chain starts the terms are allowed to go above one million.
 */

/**
 * First off, there's no point in checking the even numbers, since each even number goes to a number smaller than it and we'll check that one.
 * Secondly, if we hit a number we've already done before then we don't need to carry on.
 * 
 * So simply set up a map (although a vector would probably be better) with the count on each, and then only iterate over the odd numbers.
 */



// Common includes
#include "common.h"



// The maximum value to go to
static const uint64_t max = 1000000;

// A vector of chain lengths
static std::vector<uint64_t> chainLengths;



// A function for recursively evaluating the chain
static uint64_t GetChainLength (uint64_t value)
{
	uint64_t length;
	
	// If it's not set yet or it's too big to be stored then recurse
	if (value >= max || chainLengths[value] == 0)
	{
		if ((value % 2) == 0)
		{
			length = GetChainLength(value / 2) + 1;
		}
		else
		{
			length = GetChainLength(3 * value + 1) + 1;
		}
		
		// Set it in the mapping
		if (value < max)
			chainLengths[value] = length;
	}
	else
	{
		length = chainLengths[value];
	}
	
	// Return the value from the mapping
	return length;
}



// Begin the solution
SOLUTION_BEGIN(14, uint64_t)
{
	// Set up the vector
	// We have to use 0 here as the "not-yet-set" length since we don't know the upper bound, and it doesn't matter
	// since we're only looking for the longest chain, not how long it actually is
	chainLengths.resize(max, 0);
	
	// Make sure the chain length for 1 is set
	chainLengths[1] = 1;
	
	// Keep track of the longest chain length
	uint64_t longestChain = 0;
	
	// Go through each number and get the chain length
	for (uint64_t i=1; i<max; i+=2)
	{
		uint64_t length = GetChainLength(i);
		
		// See if it was longer than the last
		if (length > longestChain)
		{
			longestChain = length;
			result = i;
		}
	}
}
SOLUTION_END()
