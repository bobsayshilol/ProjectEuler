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
#include <string>
#include <vector>
#include <map>



/**
 * A list of solved problems for producing lists at compile time
 * Each macro must be of the form
 *   macro(problem_number, return_type, expected_result)
 * The results are taken from projecteuler-solutions
 */
#define SOLUTION_LIST(custom_macro) \
	custom_macro(1, uint64_t, 233168) \
	custom_macro(2, uint64_t, 4613732) \
	custom_macro(3, uint64_t, 6857) \
	custom_macro(4, uint64_t, 906609) \
	custom_macro(5, uint64_t, 232792560) \
	custom_macro(6, uint64_t, 25164150) \
	custom_macro(7, uint64_t, 104743) \
	custom_macro(8, uint64_t, 23514624000) \
	custom_macro(9, uint64_t, 31875000) \
	custom_macro(10, uint64_t, 142913828922) \
	custom_macro(11, uint64_t, 70600674) \
	custom_macro(12, uint64_t, 76576500) \
	custom_macro(13, uint64_t, 5537376230) \
	custom_macro(14, uint64_t, 837799) \
	custom_macro(15, uint64_t, 137846528820) \
	custom_macro(16, uint64_t, 1366) \



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



// Declare each function for the linker.
// This could just go in main.cpp...
#define SOLUTION_DECLARATION(problem_number, return_type, ...) SOLUTION_ENTRY(problem_number, return_type) ;
SOLUTION_LIST( SOLUTION_DECLARATION )



// Not much else here


#endif // EULER_COMMON_H
