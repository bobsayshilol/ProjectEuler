/**
 * Lexicographic permutations
 * 
 * A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
 * 012   021   102   120   201   210
 * What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
 */

/**
 * There are 9! permutations since there are 9 ways to choose the first digit, 8 ways to choose the next, etc...
 * 
 * Since the permutations are in order we can see that the first digit of a permutation depends on the how far
 * into the arrangement we are: ie
 * [012, 021], [102, 120], [201, 210]
 * 
 * So we have that the first digit is given by:
 * digit = position * digit_choices / total_permutations
 * Since total_permutations = digit_choices! we can simplify this and just use
 * digit = position / (digit_choices-1)!
 * 
 * We can recurse this and build up the result backwards
 */



// Common includes
#include "common.h"



// Factorial function
static constexpr uint64_t Factorial(uint64_t N)
{
	return (N == 0) ? 1 : (N * Factorial(N-1));
}



// Begin the solution
SOLUTION_BEGIN(24, uint64_t)
{
	// The lexicographic permutation to find
	constexpr uint64_t permutation = 1000000;
	
	// The number of digits (including 0)
	constexpr size_t digits = 10;
	
	
	// Create a list of used digits that we set once used
	bool usedDigits[digits+1] = { false };
	
	// The current permutation to look for
	// Note that we take away 1 from permutation since it's 1-based
	uint64_t perm = permutation - 1;
	
	// Initialise the result
	result = 0;
	
	for (size_t i=0; i<digits; i++)
	{
		// Calculate the total number of permutations for the remaining digits
		const uint64_t totalPerms = Factorial(digits - i - 1);
		
		// Get the "group" that we're in
		const uint64_t group = perm / totalPerms;
		
		// Map the group to a digit
		uint64_t digit = group;
		for (size_t j=0; j<=digit; j++)
		{
			if (usedDigits[j])
				digit++;
		}
		usedDigits[digit] = true;
		
		// Add it to the result
		result = result * 10 + digit;
		
		// Knock down the value of perm to the next group
		perm -= group * totalPerms;
	}
}
SOLUTION_END()
