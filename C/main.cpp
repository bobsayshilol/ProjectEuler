// Include the common header
#include "common.h"



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
	custom_macro(17, uint64_t, 21124) \
	custom_macro(18, uint64_t, 1074) \
	custom_macro(19, uint64_t, 171) \
	custom_macro(20, uint64_t, 648) \
	custom_macro(21, uint64_t, 31626) \
	custom_macro(22, uint64_t, 871198282) \
	custom_macro(23, uint64_t, 4179871) \
	custom_macro(24, uint64_t, 2783915460) \



// Declare each function for the linker.
// This could just go in main.cpp...
#define SOLUTION_DECLARATION(problem_number, return_type, ...) SOLUTION_ENTRY(problem_number, return_type) ;
SOLUTION_LIST( SOLUTION_DECLARATION )



/**
 * Timers for timing each solution
 */
#include <chrono>



/**
 * Simple checker template
 */
template <class T>
void CheckSolution(uint64_t problem_number, T (&solution_function)(), T expected)
{
	// Star the timer
	auto startTime = std::chrono::high_resolution_clock::now();
	
	// Get the value
	const T calculated = solution_function();
	
	// Stop the timer
	auto stopTime = std::chrono::high_resolution_clock::now();
	
	// Get the difference
	 std::chrono::duration<double, std::milli> ms = stopTime - startTime;
	
	// Log the start of the message
	printf("Solution %" PRIu64 " took %fms and ", problem_number, ms.count());
	
	// TODO: might need to give a bit of leeway here for floats
	if (calculated != expected)
	{
		// Lazily let std::to_string() handle it
		printf("failed: %s != %s\n", std::to_string(calculated).c_str(), std::to_string(expected).c_str());
	}
	else
	{
		printf("succeeded: %s\n", std::to_string(calculated).c_str());
	}
}



// main entry point
int main(int argc, char ** argv)
{
	// Only run specific solutions if requested
	if (argc != 1)
	{
		for (int i=1; i<argc; i++)
		{
			// If argv[i] isn't a valid number it'll return 0, which is nice because we start at 1
			int problem = std::atoi(argv[i]);
			
			// Should probably do more than contiune - might be something like --help
			if (problem == 0)
				continue;
			
			switch (problem)
			{
#define CASE(problem_number, return_type, expected_result) \
				case problem_number: \
					CheckSolution<return_type>(problem_number, solution_ ## problem_number, expected_result); \
					break;
					
				SOLUTION_LIST(CASE)
					
#undef CASE
				default:
					printf("Haven't done problem %i yet\n", problem);
					break;
			}
		}
		
		// Early exit
		return 0;
	}
	
	// Simply pass this on to the template above
#define CHECK_RESULT(problem_number, return_type, expected_result) \
	CheckSolution<return_type>(problem_number, solution_ ## problem_number, expected_result);
	
	SOLUTION_LIST(CHECK_RESULT)
	
#undef CHECK_RESULT
    
    return 0;
}
