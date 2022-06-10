#ifndef TP2_TIMING_HEADER
#define TP2_TIMING_HEADER

#include <stdio.h>

#include <sys/resource.h>
#include <unistd.h>

extern FILE * timingstdout;

typedef struct timing_t {
	struct rusage rstart;
	struct rusage rend;
} timing;

void t_Start(timing * t);
void t_Finalize(timing * t);

void t_PrintHeader();
void t_Print(timing * t, const char * functionName, int M, int T);

#endif
