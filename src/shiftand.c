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
static void sh_DefineBitMask(mask * mask_List, int alfabet_size, note * suspect, int T);
static void sh_FindPatternSuspect(mask * mask_List, note * suspect, note * original, int M, int T);

static void toBinary(int n, int len);
static void printMasks(mask * mask_List, int M);
static void printAlfabet(note * alfabet, int size);

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

    for (int i = 0; i < M; i++) {
        note first_alfabet_note = original[i];
        alfabet[first_alfabet_note] = first_alfabet_note;
        *(current_size) = *(current_size) + 1;
    }
    
    return alfabet;
}

static void sh_DefineBitSequencesTo0(mask * mask_list, note * alfabet, int alfabet_size) {
    for (int i = 0; i < alfabet_size; i++) {
        mask_list[i].element = alfabet[i];
        mask_list[i].bit_sequence = 0;
    }
}

static void sh_DefineBitMask(mask * mask_List, int alfabet_size, note * suspect, int T) {
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

static void sh_FindPatternSuspect(mask * mask_List, note * suspect, note * original, int M, int T) {
    int result = 0, result_alt = 0;
    int areSimilar, count;
    short last_distance;
    for (int i = 0; i < M; i++) {
        note suspect_note = original[i];

        result = (result >> 1) | 1 << (T - 1); 
        result_alt = result & mask_List[suspect_note].bit_sequence;
        
        //areSimilar = nt_areSimilars(suspect_note, suspect[count], &last_distance);
        printf("%d\n", count); 

        if (((result_alt & (01)) != 0)) {
            printf("S %d\n", (i - T + 1));
            //return;
        }   
    }
    printf("N\n");
}

    //11 >> 1 = 01
    //11 << 1 = 110

void shiftand(note * original, int M, note * suspect, int T) {
    int alfabet_size = 0;
    note * original_Alfabet = sh_GetAlfebet(original, M, &alfabet_size);

    mask * mask_List = (mask *) malloc(sizeof(mask) * alfabet_size);

    alfabet_size = 12;

    sh_DefineBitSequencesTo0(mask_List, original_Alfabet, alfabet_size);

    sh_DefineBitMask(mask_List, alfabet_size, suspect, T);

    sh_FindPatternSuspect(mask_List, suspect, original, M, T);

    //printAlfabet(original_Alfabet, alfabet_size);
    //printMasks(mask_List, M);
    printf("----------\n");

} 

static void printMasks(mask * mask_List, int M) {
    for (int i = 0; i < M; i++) {
        printf("Note %d: ", mask_List[i].element);
        toBinary(mask_List[i].bit_sequence, 64);
    }
}

static void printAlfabet(note * alfabet, int size) {
    for (int i = 0; i < size; i++) {
        printf("i: %d\n", alfabet[i]);
    }
}

static void toBinary(int n, int len) {
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