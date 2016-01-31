// Include the common header
#include "common.h"



/**
 * Timers for timing each solution
 */
#include <chrono>



/**
 * Simple checker template
 */
template <uint64_t problem_number, class T, T expected>
void CheckSolution(T (&solution_function)())
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
int main()
{
	// Macro magic to test each result
#define CHECK_RESULT(problem_number, return_type, expected_result) \
{ \
	/* Pass this on to the template above */ \
	CheckSolution<problem_number, return_type, expected_result>(solution_ ## problem_number); \
};
	SOLUTION_LIST(CHECK_RESULT)
    
    return 0;
}
