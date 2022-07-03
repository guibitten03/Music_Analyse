#include "naivestringmatching.h"

#include <stdio.h>

#ifdef TIMING
#include "timing.h"
#endif

extern FILE * outputFile;

void naiveStringMatching(note * O, int n, note * S, int m) {
#ifdef TIMING
	timing t;
	t_Start(&t);
#endif
	for (int i = 0; i < n - m + 1; i++) {
		int k = i;
		int j = 0;

		short lastDistance = -1;
		while (nt_areSimilars(O[k], S[j], &lastDistance)) {
			k++; j++;
			if (j == m) {
#ifdef TIMING
				t_Finalize(&t);
				t_Print(&t, __func__, n, m);
#endif
				fprintf(outputFile, "S %d\n", i);
				return;	
			}
		}
	}
#ifdef TIMING
	t_Finalize(&t);
	t_Print(&t, __func__, n, m);
#endif
	fprintf(outputFile, "N\n");
}