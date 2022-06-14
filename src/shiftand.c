#include "shiftand.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef u_int64_t note_64; 

/*
    C, B# = 0
    Db, C# = 8
    D = 16
*/

typedef struct mask_t mask;
typedef struct mask * Mask;

struct mask_t {
    note element;
    int last_bit;
    note_64 bit_sequence;
};


static note * sh_GetAlfebet(note * original, int M, int * current_size);
static int sh_CompairElementsOnAlfabet(note * alfabet, int current_size, int nextOE);
static void sh_DefineBitSequencesTo0(mask * mask_list, note * alfabet, int alfabet_size);
static void sh_DefineBitMask(mask_List, alfabet_size, suspect, T);

static void toBinary(int n, int len);

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

void sh_DefineBitSequencesTo0(mask * mask_list, note * alfabet, int alfabet_size) {
    for (int i = 0; i < alfabet_size; i++) {
        mask_list[i].element = alfabet[i];
        mask_list[i].bit_sequence = 0;
    }
}

void sh_DefineBitMask(mask * mask_List, int alfabet_size, note * suspect, int T) {
    int current_element;

    for (int i = 0; i < T; i++) {
        current_element = suspect[i];

        for (int j = 0; j < alfabet_size; j++) {
            if (current_element == mask_List[j].element) {
                mask_List[j].bit_sequence = mask_List[j].bit_sequence | 1 << (T - i - 1);
            }
        }
    }
}

void sh_FindPatternSuspect(mask * mask_List, note * original, int alfabet_size, int M, int T) {
    int result = 0, result_alt = 0;
    for (int i = 0; i < M; i++) {
        int suspect_note = original[i];
        printf("%d\n", suspect_note);

        result = (result_alt >> 1) | 1 << (T - 1); 
        result_alt = result & mask_List[i].bit_sequence;
    }
}

    //11 >> 1 = 01
    //11 << 1 = 110

void shiftand(note * original, int M, note * suspect, int T) {
    int alfabet_size = 0;
    note * original_Alfabet = sh_GetAlfebet(original, M, &alfabet_size);

    mask * mask_List = (mask *) malloc(sizeof(mask) * alfabet_size);

    sh_DefineBitSequencesTo0(mask_List, original_Alfabet, alfabet_size);

    sh_DefineBitMask(mask_List, alfabet_size, suspect, T);

    sh_FindPatternSuspect(mask_List, original, alfabet_size, M, T);
} 


void toBinary(int n, int len) {
    char* binary = (char*)malloc(sizeof(char) * len);
    int k = 0;
    for (unsigned i = (1 << len - 1); i > 0; i = i / 2) {
        binary[k++] = (n & i) ? '1' : '0';
    }
    binary[k] = '\0';

    printf("The binary representation of %d is %s\n", n, binary);
    free(binary);
    return;
}