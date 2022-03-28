#include "utils.hpp"

double Timer()
{
	static clock_t t1 = 0, t2 = 0;

	t2 = clock();
	double elapsed = (double)(t2 - t1) / CLOCKS_PER_SEC;
	t1 = t2;

	return elapsed;
}