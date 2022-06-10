#include "bruteforce.h"

#include <stdio.h>

void bruteForce(note * original, int M, note * suspect, int T) {
	for (int i = 0; i < M - T + 1; i++) {
		int k = i;
		int j = 0;

		short lastDistance = -1;
		while (nt_areSimilars(original[k], suspect[j], &lastDistance)) {
			k++; j++;
			if (j == T) {
				printf("S %d\n", i);
				return;	
			}
		}
	}
	printf("N\n");
}