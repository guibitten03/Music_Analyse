#include "shiftand.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef u_int32_t note_32; 

/*
    C, B# = 0
    Db, C# = 8
    D = 16
*/

typedef struct mask_t mask;
typedef struct mask * Mask;

struct mask_t {
    note_32 bit_sequence;
};


static note * sh_GetAlfebet(note * original, int M, int * current_size);
static int sh_CompairElementsOnAlfabet(note * alfabet, int current_size, int nextOE);
static void sh_DefineBitSequencesTo0(mask * mask_list, int alfabet_size, note * suspect, int suspect_size);

static int sh_CompairElementsOnAlfabet(note * alfabet, int current_size, int nextOE) {
    for (int i = 0; i < current_size; i++) {
        if (alfabet[i] == nextOE) {
            return 0;
        }
    }
    return 1;
}

static note * sh_GetAlfebet(note * original, int M, int * current_size) {
    note * alfabet = (note *) malloc(sizeof(note) * M);

    for (int i = 0; i < M; i++) {
        alfabet[i] = -1;
    }

    alfabet[0] = original[0];
    *(current_size) = *(current_size) + 1;

    for (int i = 1; i < M; i++) {
        int nextOriginalElement = original[i];
        if ( sh_CompairElementsOnAlfabet(alfabet, *(current_size), nextOriginalElement) ) {
            int indexOfNewElement = *(current_size);
            *(current_size) = *(current_size) + 1;
            alfabet[indexOfNewElement] = nextOriginalElement;
        } else {
            continue;
        }
    }
    
    return alfabet;
}

void sh_DefineBitSequencesTo0(mask * mask_list, int alfabet_size, note * suspect, int suspect_size) {
    for (int i = 0; i < alfabet_size; i++) {
        mask_list->bit_sequence =  && ;
    }
}

void sh_DefineBitMask(mask_List, alfabet_size, suspect, T) {
    for (int i = 0; i < alfabet_size; i++) {

    }
}

void shiftand(note * original, int M, note * suspect, int T) {
    // pre process
    // For each original element, create a mask with each suspect element
    // Making a mask type array
    
    int alfabet_size = 0;
    note * original_Alfabet = sh_GetAlfebet(original, M, &alfabet_size);

    // Make masks of ocorrences
    mask * mask_List = (mask *) malloc(sizeof(mask) * alfabet_size);

    sh_DefineBitSequencesTo0(mask_List, alfabet_size, suspect, T);

    sh_DefineBitMask(mask_List, alfabet_size, suspect, T);

    printf("%d", mask_List[0].bit_sequence);

    free(original_Alfabet);
    free(mask_List);

} 