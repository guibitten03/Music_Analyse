#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashAlphabet(ch) ((int)(ch) - 97)

const int szAlphabet = 26;
const char alphabet[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p','q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

void BMH(char * T, int n, char * P, int m);

void BMH_preprocessing(int * pos, char * P, int m);

void main(int argc, char ** argv) {
    char * T = argv[1];
    int n = strlen(T);

    char * P = argv[2];
    int m = strlen(P);

    BMH(T, n, P, m);
}

void BMH(char * T, int n, char * P, int m) {
    int pos[szAlphabet];

    BMH_preprocessing(pos, P, m);

    for (int i = m - 1; i < n; i++) {
        printf("%s\n", T);
        for (int l = 0; l < i - (m - 1); l++) printf("-");
        printf("%s\n", P);

        int k = i;
        int j = m - 1;

        while (T[k] == P[j]) {
            if (j == 0) {
                printf("S %d\n", k);
                return;
            }

            k--; j--;
        }

        i = i + pos[hashAlphabet(T[k])];
        i--;
    }

    printf("N\n");
}

void BMH_preprocessing(int * preprocessingTable, char * P, int m) {
    for (int i = 0; i < szAlphabet; i++) {
        preprocessingTable[i] = m;
    }

    for (int i = 0; i < m - 1; i++) {
        preprocessingTable[hashAlphabet(P[i])] = m - i - 1;
    }
}