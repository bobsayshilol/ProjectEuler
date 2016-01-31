// Include the common header
#include "common.h"



/**
 * Timers for timing each solution
 */
#include <time.h>

// Start a timer
#define TIMER_START() \
do { \
    \
} while(0)

// Stop a timer
#define TIMER_STOP() \
do { \
    \
} while(0)



/**
 * Simple checker template
 */
template <uint64_t problem_number, class T, T expected>
void CheckSolution(T (&solution_function)())
{
	// Get the value
	// TODO: time it!
	const T calculated = solution_function();
	
	// TODO: might need to give a bit of leeway here for floats
	if (calculated != expected)
	{
		// Lazily let std::to_string() handle it
		printf("Solution %" PRIu64 " failed: %s != %s\n", problem_number, std::to_string(calculated).c_str(), std::to_string(expected).c_str());
	}
	else
	{
		printf("Solution %" PRIu64 " succeeded: %s\n", problem_number, std::to_string(calculated).c_str());
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
