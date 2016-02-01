/**
 * Number letter counts
 * 
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
 * NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
 */

/**
 * Special case 1000 = sizeof("one" + "thousand")
 * Between XX1 and XX9 we will always have 1-9 appear once as the last digit, so we have 100 * sizeof("one" + "two" + ... + "nine")
 * But for one in every 10 cases of the above we need to use "eleven", "twelve", etc... instead
 * Between X20 and X90 we will always have 1-9 appear once as the tens digit, so we have 10 * 10 * sizeof("twenty" + ... + "ninety")
 * We also need to add X10, so we have 10 * sizeof("ten")
 * Between 100 and 999 we will always have 1-9 appear once as the hundred digit, so we have 100 * sizeof("one" + "two" + ... + "nine")
 * Between 100 and 999 we will always have "hundred" appear, so we have 9 * 100 * sizeof("hundred")
 * "and" will appear for any number >= 100 that isn't divisible by 100, so we have (9 * 100 - 9) * sizeof("and")
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(17, uint64_t)
{
	// The strings to use
#define DEFINE_STRING(str) \
	const char str ## _string[] = #str; \
	const size_t sizeof_ ## str = sizeof( str ## _string ) / sizeof( str ## _string [0]) - 1;
	
	DEFINE_STRING(one);
	DEFINE_STRING(two);
	DEFINE_STRING(three);
	DEFINE_STRING(four);
	DEFINE_STRING(five);
	DEFINE_STRING(six);
	DEFINE_STRING(seven);
	DEFINE_STRING(eight);
	DEFINE_STRING(nine);
	
	DEFINE_STRING(eleven);
	DEFINE_STRING(twelve);
	DEFINE_STRING(thirteen);
	DEFINE_STRING(fourteen);
	DEFINE_STRING(fifteen);
	DEFINE_STRING(sixteen);
	DEFINE_STRING(seventeen);
	DEFINE_STRING(eighteen);
	DEFINE_STRING(nineteen);
	
	DEFINE_STRING(ten);
	DEFINE_STRING(twenty);
	DEFINE_STRING(thirty);
	DEFINE_STRING(forty);
	DEFINE_STRING(fifty);
	DEFINE_STRING(sixty);
	DEFINE_STRING(seventy);
	DEFINE_STRING(eighty);
	DEFINE_STRING(ninety);
	
	DEFINE_STRING(hundred);
	DEFINE_STRING(and);
	DEFINE_STRING(thousand);
	
#undef DEFINE_STRING
	
	// The size of "one" + "two" + ... + "nine"
	const size_t sizeof_one_to_nine =	sizeof_one + sizeof_two + sizeof_three +
										sizeof_four + sizeof_five + sizeof_six +
										sizeof_seven + sizeof_eight + sizeof_nine;
	
	// The size of "ten" + "eleven" + ... + "nineteen"
	const size_t sizeof_eleven_to_nineteen =	sizeof_ten + sizeof_eleven + sizeof_twelve + sizeof_thirteen +
												sizeof_fourteen + sizeof_fifteen + sizeof_sixteen +
												sizeof_seventeen + sizeof_eighteen + sizeof_nineteen;
	
	// The size of "twenty" + ... + "ninety"
	const size_t sizeof_twenty_to_ninety =	sizeof_twenty + sizeof_thirty +
											sizeof_forty + sizeof_fifty + sizeof_sixty +
											sizeof_seventy + sizeof_eighty + sizeof_ninety;
	
	// The XX1-XX9 bit
	const uint64_t units_digit_sum = (100 - 10) * sizeof_one_to_nine;
	
	// The X20-X90 bit
	const uint64_t tens_digit_sum = 10 * 10 * sizeof_twenty_to_ninety;
	
	// The 100-999 bit
	const uint64_t hundreds_digit_sum = 100 * sizeof_one_to_nine;
	
	// "ten", "eleven", ... appearances
	const uint64_t ten_sum = 10 * sizeof_eleven_to_nineteen;
	
	// "hundred" appearances
	const uint64_t hundred_sum = 9 * 100 * sizeof_hundred;
	
	// "and" appearances
	const uint64_t and_sum = (9 * 100 - 9) * sizeof_and;
	
	// Special case 1000
	const uint64_t thousand_sum = sizeof_thousand + sizeof_one;
	
	// Add up the parts
	result = units_digit_sum + tens_digit_sum + hundreds_digit_sum + ten_sum + hundred_sum + and_sum + thousand_sum;
}
SOLUTION_END()
