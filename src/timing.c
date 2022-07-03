#include "timing.h"

void t_Start(timing * t) {
	getrusage(RUSAGE_SELF, &t->rstart);
}

void t_Finalize(timing * t) {
	getrusage(RUSAGE_SELF, &t->rend);
}

void t_PrintHeader() {
	fprintf(timingstdout, "function|n|m|n*m|userTime\n");
}

void t_Print(timing * t, const char * function, int n, int m) {
	float userTime = (t->rend.ru_utime.tv_sec - t->rstart.ru_utime.tv_sec) + 1e-6 * (t->rend.ru_utime.tv_usec - t->rstart.ru_utime.tv_usec);
	fprintf(timingstdout, "%s|%d|%d|%d|%0.6f\n", function, n, m, n * m, userTime);
}
