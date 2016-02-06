/**
 * Counting Sundays
 * 
 * You are given the following information, but you may prefer to do some research for yourself.
 *    1 Jan 1900 was a Monday.
 *    Thirty days has September,
 *    April, June and November.
 *    All the rest have thirty-one,
 *    Saving February alone,
 *    Which has twenty-eight, rain or shine.
 *    And on leap years, twenty-nine.
 *    A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
 * How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
 */

/**
 * 365 mod 7 = 1
 * => 1 Jan 1901 was a Tuesday
 * Brute force loop by keeping track of the current day mod 7 and adding on the number of days in each month
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(19, uint64_t)
{
	// Set the years.
	// Goes from 1 Jan <firstYear> to 31 Dec <lastYear>
	const uint64_t firstYear = 1901;
	const uint64_t lastYear = 2000;
	
	// And the start day
	// 0 = Monday, 1 = Tuesday, ...
	const uint64_t startDay = 1;
	
	// Function to get the number of days in the month
	auto GetDayCount = [](uint64_t year, uint64_t month)
	{
		uint64_t count = 0;
		
		// Do the lookup
		const uint64_t dayCount[12] = {
			31,
			28,
			31,
			30,
			31,
			30,
			31,
			31,
			30,
			31,
			30,
			31,
		};
		count = dayCount[month];
		
		// Check if this is February in a leap year
		if (( month == 1 )				&&	// February
			( (year % 4) == 0 )			&&	// Leap year
			( ( (year % 100) != 0 )		||	// Not a century
				( (year % 400) == 0 )	)	// Unless divisible by 400
		   )
		{
			count++;
		}
		
		return count;
	};
	
	// Initialise the result
	result = 0;
	
	// Current day
	// 0 = Monday, 1 = Tuesday, ...
	uint64_t currentDay = startDay;
	
	// Go through each year
	for (uint64_t year=firstYear; year<=lastYear; year++)
	{
		// Go through each month
		for (uint64_t month=0; month<12; month++)
		{
			// Check for a Sunday
			if (currentDay == 6)
				result++;
			
			// Then add on the days in this month
			currentDay += GetDayCount(year, month);
			
			// And mod it
			currentDay %= 7;
		}
	}
}
SOLUTION_END()
