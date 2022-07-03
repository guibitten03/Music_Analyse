#include "bmh.h"

#include <stdio.h>

#ifdef TIMING
#include "timing.h"
#endif

extern FILE * outputFile;

static void BMH_preprocessing(int * table, note * S, int m);

void BMH(note * O, int n, note * S, int m) {
#ifdef TIMING
	timing t;
	t_Start(&t);
#endif
    int table[szAlphabet];

    BMH_preprocessing(table, S, m);

    int i = m - 1;
    while (i < n) {
        int k = i;
        int j = m - 1;
        short lastDistance = -1;

        while (nt_areSimilars(O[k], S[j], &lastDistance)) {
            if (j == 0) {
#ifdef TIMING
            t_Finalize(&t);
            t_Print(&t, __func__, n, m);
#endif
                fprintf(outputFile, "S %d\n", k);
                return;
            }

            k--; j--;
        }

        i = i + table[nt_Hash(O[k])];
    }
#ifdef TIMING
	t_Finalize(&t);
	t_Print(&t, __func__, n, m);
#endif
    fprintf(outputFile, "N\n");
}

static void BMH_preprocessing(int * table, note * S, int m) {
    for (int i = 0; i < szAlphabet; i++) {
        table[i] = m - 1;
    }

    for (int i = 0; i < m - 1; i++) {
		for (int j = 0; j < szAlphabet; j++) {
			short _ = -1;
			if (nt_areSimilars(S[i], j, &_)) {
				table[j] = m - i - 1;
			}
		}
    }
}
