#include "shiftand.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define SIZE_DISTANCE_MASKS 7
extern FILE * outputFile;

typedef uint64_t mask_64;

typedef struct mask_t mask;
typedef struct mask * Mask;

struct mask_t {
    note element;
    mask_64 * bitSequences;
};


static note * SA_GetAlfebet();
static void SA_DefineBitSequencesTo0(mask * mask_list);
static void SA_DefineMasksForEachNote(mask noteT, note * suspect, int T);
static void SA_DefineBitMask(mask * mask_List, note * suspect, int T);
static void SA_FindSuspectPattern(mask * mask_List, note * original, int M, int T);
static void SA_FreeBitMasks(mask * maskList);


void shiftand(note * original, int M, note * suspect, int T) {
    #ifdef TIMING
	    timing t;
	    t_Start(&t);
    #endif
    note * originalAlfabet = SA_GetAlfebet();

    mask * maskList = (mask *) malloc(sizeof(mask) * szAlphabet);

    SA_DefineBitSequencesTo0(maskList);

    SA_DefineBitMask(maskList, suspect, T);

    SA_FindSuspectPattern(maskList, original, M, T);

    SA_FreeBitMasks(maskList);
    free(maskList);
    free(originalAlfabet);
    #ifdef TIMING
            t_Finalize(&t);
            t_Print(&t, __func__, n, m);
    #endif
} 

static note * SA_GetAlfebet() {
    note * alfabet = (note *) malloc(sizeof(note) * szAlphabet);
    for (int i = 0; i < szAlphabet; i++) {
        alfabet[i] = i;
    }
    
    return alfabet;
}

static void SA_DefineBitSequencesTo0(mask * maskList) {
    for (int i = 0; i < szAlphabet; i++) {
        maskList[i].element = i;
        maskList[i].bitSequences = (mask_64*) malloc(sizeof(mask_64) * SIZE_DISTANCE_MASKS);
        for (int j = 0; j < SIZE_DISTANCE_MASKS; j++) {
            maskList[i].bitSequences[j] = 0;
        }
    }
}

static void SA_DefineBitMask(mask * mask_List, note * suspect, int T) {
    for (int i = 0; i < szAlphabet; i++) {
        SA_DefineMasksForEachNote(mask_List[i], suspect, T);
    }
}

static void SA_DefineMasksForEachNote(mask noteT, note * suspect, int T) {
    int vectorOfDistances[SIZE_DISTANCE_MASKS] = {0,1,2,4,8,10,11};

    for (int i = 0; i < T; i++) {
        int suspectNote = suspect[i];

        for (int distance = 0; distance < SIZE_DISTANCE_MASKS; distance++) {
            int elementPlusDistance = (noteT.element + vectorOfDistances[distance]) % 12;
            if (elementPlusDistance == suspectNote) {
                noteT.bitSequences[distance] = noteT.bitSequences[distance] | 1 << (T - i - 1);
            }
        }
    }
}

static void SA_FindSuspectPattern(mask * maskList, note * original, int M, int T) {

    for (int distance = 0; distance < SIZE_DISTANCE_MASKS; distance++) {
        mask_64 result = 0;
        for (int tNote = 0; tNote < M; tNote++) {
            note suspectNote = original[tNote];

            result = (result >> 1) | 1 << (T - 1); 
            result = result & maskList[suspectNote].bitSequences[distance];

            if (((result & (01)) != 0)) {
                fprintf(outputFile, "S %d\n", (tNote - T + 1));
                return;
            }   
        }
    }
    fprintf(outputFile, "N\n");
}

static void SA_FreeBitMasks(mask * maskList) {
    for (int i = 0; i < szAlphabet; i++) {
        free(maskList[i].bitSequences);
    }
}