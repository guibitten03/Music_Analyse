#include "bmh.h"

#include <stdlib.h>
#include <stdio.h>

static void BMH_preprocessing(int * pos, note * P, int m);

void BMH(note * original, int M, note * suspect, int T) {
    int pos[szAlphabet];

    BMH_preprocessing(pos, suspect, T);

    for (int i = T - 1; i < M; i++) {
        int k = i;
        int j = T - 1;
        short lastDistance = -1;

        while (nt_areSimilars(original[k], suspect[j], &lastDistance)) {
            if (j == 0) {
                printf("S %d\n", k);
                return;
            }

            k--; j--;
        }

        i = i + pos[nt_Hash(original[k])];
        i--;
    }
    printf("N\n");
}

static void BMH_preprocessing(int * preprocessingTable, note * P, int m) {
    for (int i = 0; i < szAlphabet; i++) {
        preprocessingTable[i] = m - 1;
    }

    for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < szAlphabet; j++) {
			short dist = -1;
			if (nt_areSimilars(P[i], j, &dist)) {
				preprocessingTable[j] = m - i - 1;
			}
		}
    }
}
