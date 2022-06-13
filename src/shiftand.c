#include "shiftand.h"

#include <stdio.h>
#include <stdlib.h>

// const note C, B# = 0;
// note
// const note D = 2;
// const note E = 4;
// const note F = 5;
// const note G = 7;
// const note A = 9;
// const note B = 11;

static note * sh_GetAlfebet(note * original, int M);

struct mask_t {
    int * bit_sequence;
};

typedef struct mask_t mask;
typedef struct mask * Mask;

// method to descovered the alfabet
static note * sh_GetAlfebet(note * original, int M) {
    note * alfabet = (note *) malloc(sizeof(note) * M);

    for (int i = 0; i < M; i++) {
        alfabet[i] = -1;
    }

    int current_size = 0, current_position = 0;
    alfabet[0] = original[0];
    for (int i = 0; i < M; i++) {
        for (int j = 1; j < M; j++){
            if (original[j] != alfabet[current_position]) {
                current_size++;
                current_position = 0;
                alfabet[current_size] = original[j];
            }else {
                current_position++;
            }
        }
    }
}

void shiftand(note * original, int M, note * suspect, int T) {
    // pre process
    // For each original element, create a mask with each suspect element
    // Making a mask type array
    mask * mask_patterns = (mask*) malloc(sizeof(mask) * M);

    //note * original_Alfabet = sh_GetAlfebet(original, M);

    // Creating the masks of each element 
    for (int i = 0; i < M; i++){
        mask_patterns[i].bit_sequence = (int *) malloc(sizeof(int) * T);
    }

}