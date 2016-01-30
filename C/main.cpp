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
		// For now just print these as doubles
		printf("Solution %" PRIu64 " failed: %g != %g\n", problem_number, static_cast<double>(calculated), static_cast<double>(expected));
	}
	else
	{
		printf("Solution %" PRIu64 " succeeded: %g\n", problem_number, static_cast<double>(calculated));
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
