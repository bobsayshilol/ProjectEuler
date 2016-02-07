// Include the common header
#include "common.h"



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
