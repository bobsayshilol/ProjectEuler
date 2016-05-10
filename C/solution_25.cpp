/**
 * 1000-digit Fibonacci number
 * 
 * The Fibonacci sequence is defined by the recurrence relation:
 *    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
 * Hence the first 12 terms will be:
 *    F1 = 1
 *    F2 = 1
 *    F3 = 2
 *    F4 = 3
 *    F5 = 5
 *    F6 = 8
 *    F7 = 13
 *    F8 = 21
 *    F9 = 34
 *    F10 = 55
 *    F11 = 89
 *    F12 = 144
 * The 12th term, F12, is the first term to contain three digits.
 * What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
 */

/**
 * Let F(n) = nth Fibonacci number with F(1) = F(2) = 1, then it can be shown that F(n) = (phi^n - (-phi)^-n)/sqrt(5), phi = (1+sqrt(5))/2
 * (see problem 2)
 * 
 * We are looking for N st F(N) >= 10^K and F(N-1) < 10^K
 * Since F(N) is going to be very very large we can assume that phi^-N ~= 0, leaving us with
 * F(N) ~= (phi^N)/sqrt(5)
 * F(N) >= 10^K
 * => phi^N >= sqrt(5) * 10^K
 * => N >= (ln(sqrt(5)) + K * ln(10))/ln(phi)
 */



// Common includes
#include "common.h"



// Begin the solution
SOLUTION_BEGIN(25, uint64_t)
{
	// The number of digits to find
	constexpr size_t digits = 1000;
	
	
	// Calculate some constants
	static const double sqrt5 = sqrt(5);
	static const double phi = (1.0 + sqrt5) / 2.0;
	static const double sqrt5logphi = log(sqrt5)/log(phi);
	static const double tenlogphi = log(10.0)/log(phi);
	
	// Calculate N as above and round it up for >
	// Note that we need to take away 1 here since the number of digits isn't the same as power of 10 (10^0 has 1 digit)
	uint64_t N = std::ceil(sqrt5logphi + (digits-1) * tenlogphi);
	
	// And that's the result
	result = N;
}
SOLUTION_END()
