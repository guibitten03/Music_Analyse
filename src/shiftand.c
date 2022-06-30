#include "shiftand.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

// Caminho de dados
// Multiplicação e divisão
// Risc e Cisc
// 

typedef u_int64_t mask_64; 

/*
    C, B# = 0
    Db, C# = 8
    D = 16
*/

typedef struct mask_t mask;
typedef struct mask * Mask;

struct mask_t {
    note element;
    mask_64 bit_sequence;
};


static note * sh_GetAlfebet();
static void sh_DefineBitSequencesTo0(mask * mask_list, note * alfabet);
//static void sh_DefineBitMask(mask * mask_List, note * suspect, int T);

/* Testing */
static void sh_DefineBitMask(mask * mask_List, note * suspect, int T);
// ---

static void sh_FindSuspectPattern(mask * mask_List, note * original, int M, int T);

static void toBinary(int n, int len);
static void printMasks(mask * mask_List);

static note * sh_GetAlfebet() {
    note * alfabet = (note *) malloc(sizeof(note) * szAlphabet);

    for (int i = 0; i < szAlphabet; i++) {
        alfabet[i] = i;
    }
    
    return alfabet;
}

static void sh_DefineBitSequencesTo0(mask * mask_list, note * alfabet) {
    for (int i = 0; i < szAlphabet; i++) {
        mask_list[i].element = alfabet[i];
        mask_list[i].bit_sequence = 0;
    }
}

/* Testing */
static void sh_DefineBitMask(mask ** maskClustter, note * suspect, int T) {
    // Define all masks to 0
    
}
// ---

// static void sh_DefineBitMask(mask * mask_List, note * suspect, int T) {
//     short last_distance = -1;

//     for (int i = 0; i < T; i++) {
//         int current_element = suspect[i];

//         for (int j = 0; j < szAlphabet; j++) {
//             //int areSimilar = nt_areSimilars(current_element, mask_List[j].element, &last_distance);
//             //printf("%d - %d : %d - lastD: %d\n", current_element, mask_List[j].element, areSimilar, last_distance);
//             if (current_element == mask_List[j].element | nt_areSimilars(current_element, mask_List[j].element, &last_distance)) {
//                 mask_List[j].bit_sequence = mask_List[j].bit_sequence | 1 << (T - i - 1);
//             } else {
//                 last_distance = -1;
//             }
//         }
//     }
// }

// static void sh_ConstructDistanceText (note * text, int size) {
//     int * distanceVertices = (int*) malloc(sizeof(int) * size);
//     int lastDistance = -1;

//     distanceVertices[0] = -1;
//     for (int i = 1; i < size; i++) {
//         if (nt_areSimilars(text[i], text[i + 1], &lastDistance));
//     }
// }

static void sh_FindSuspectPattern(mask * mask_List, note * original, int M, int T) {
    int result = 0;

    for (int i = 0; i < M; i++) {
        note suspect_note = original[i];

        result = (result >> 1) | 1 << (T - 1); 
        result = result & mask_List[suspect_note].bit_sequence;

        if (((result & (01)) != 0)) {
            printf("S %d\n", (i - T + 1));
            return;
        }  
    }
    printf("N\n");
}

// Find semelhant patterns:
// Distances: 1, 2, 4, 8
// Ex: C -> C# -> D -> E -> Ab
//     0    1     2    4    8

// Bit shift logic:
// 11 >> 1 = 01
// 11 << 1 = 110

void shiftand(note * original, int M, note * suspect, int T) {
    note * original_Alfabet = sh_GetAlfebet();

    //mask * mask_List = (mask *) malloc(sizeof(mask) * szAlphabet);

    /* Testing */
    mask ** maskClustter = (mask**) malloc(sizeof(mask*) * 9);
    // ---

    //sh_DefineBitSequencesTo0(mask_List, original_Alfabet);

    //sh_DefineBitMask(mask_List, suspect, T);

    /* Testing */
    sh_DefineBitMask(maskClustter, suspect, 9);
    // ---

    //sh_FindSuspectPattern(mask_List, original, M, T);

    free(original_Alfabet);
    //free(mask_List);
} 

static void printMasks(mask * mask_List) {
    for (int i = 0; i < szAlphabet; i++) {
        printf("Note %d: ", mask_List[i].element);
        toBinary(mask_List[i].bit_sequence, 64);
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