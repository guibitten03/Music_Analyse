#include "bmh.h"

#include <stdlib.h>
#include <stdio.h>

static int BMH_hashNote(note n);

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

        i = i + pos[BMH_hashNote(original[k])];
        i--;
    }
    printf("N\n");
}

static void BMH_preprocessing(int * preprocessingTable, note * P, int m) {
    for (int i = 0; i < szAlphabet; i++) {
        preprocessingTable[i] = m - 1;
    }

    for (int i = 0; i < m - 1; i++) {
        preprocessingTable[BMH_hashNote(P[i])] = m - i - 1;
    }
}

static int BMH_hashNote(note n) {
    return ((n / 2) + (n % 2));
}
