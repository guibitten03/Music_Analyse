#include "bruteforce.h"

#include <stdio.h>

#ifdef TIMING
#include "timing.h"
#endif

void bruteForce(note * original, int M, note * suspect, int T) {
#ifdef TIMING
	timing t;
	t_Start(&t);
#endif
	for (int i = 0; i < M - T + 1; i++) {
		int k = i;
		int j = 0;

		short lastDistance = -1;
		while (nt_areSimilars(original[k], suspect[j], &lastDistance)) {
			printf("%d\n", lastDistance);
			k++; j++;
			if (j == T) {
				printf("S %d\n", i);
#ifdef TIMING
				t_Finalize(&t);
				t_Print(&t, __func__, M, T);
#endif
				return;	
			}
		}
	}
	printf("N\n");
#ifdef TIMING
	t_Finalize(&t);
	t_Print(&t, __func__, M, T);
#endif
}