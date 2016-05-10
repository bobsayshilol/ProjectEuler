/**
 * Common include for all solutions
 */
#ifndef EULER_COMMON_H
#define EULER_COMMON_H

// Common includes
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cinttypes>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>



// Entry point for each solution
#define SOLUTION_ENTRY(problem_number, return_type) \
return_type solution_ ## problem_number (void)



/**
 * Macros for wrapping each solution
 * SOLUTION_ENTRY defines the variable "result" which should then be set
 * to the result of the solution.
 * SOLUTION_END returns this value.
 */
#define SOLUTION_BEGIN(PROBLEM_NUMBER, RETURN_TYPE) \
	SOLUTION_ENTRY(PROBLEM_NUMBER, RETURN_TYPE) \
	{ \
		RETURN_TYPE result;

#define SOLUTION_END() \
	return result; \
	}



// Not much else here


#endif // EULER_COMMON_H
