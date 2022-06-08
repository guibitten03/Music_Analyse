#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define C 0b0000100000000000
#define D 0b0000001000000000
#define E 0b0000000010000000
#define F 0b0000000001000000
#define G 0b0000000000010000
#define A 0b0000000000000100
#define B 0b0000000000000001

#define SHARP(X) (rightShiftC(X))
#define FLAT(X) (leftShiftC(X))

typedef uint16_t note;

short isSimilar(note a, note b);
short checkRight(note a, note b);
short checkLeft(note a, note b);
note rightShiftLimited(note n);
note leftShiftLimited(note n);
note rightShiftC(note n);
note leftShiftC(note n);
short isPowerOf2(int n);
void printBits(note num);

int main_Example(int argc, char ** argv) {
    note a = FLAT(C);
    note b = SHARP(D); // FLAT(A);

    printBits(a);
    printBits(b);

    if (isSimilar(a, b)) {
        printf("They are similars.\n");
    } else {
        printf("They are NOT similars.\n");
    }

    if (a == b) {
        printf("They are equals.\n");
    } else {
        printf("They are NOT equals.\n");
    }

    return 0;
}

short isSimilar(note a, note b) {
    short rightResult = checkRight(a, b);
    short leftResult = checkLeft(a, b);
    return rightResult || leftResult;
}

short checkRight(note a, note b) {
    note current = a;
    note last = current;
    int i = 0;

    do
    {
        last = current;
        current = rightShiftLimited(current);
        i++;

        if (current == b) {
            if (isPowerOf2(i) && i != 1) {
                return 1;
            }
        }
    } while (current != last);
    
    return 0;
}

short checkLeft(note a, note b) {
    note last = a;
    int i = 0;

    do
    {
        last = a;
        a = leftShiftLimited(a);
        i++;

        if (a == b) {
            if (isPowerOf2(i) && i != 1) {
                return 1;
            }
        }
    } while (a != last);
    
    return 0;
}

note rightShiftLimited(note n) {
    short RMBis1 = (n & 1) != 0;
    if (RMBis1) return n;
    return n >> 1;
}

note leftShiftLimited(note n) {
    short LMBis1 = (n & 0b0000100000000000) != 0;
    if (LMBis1) return n;
    return n << 1;
}

note rightShiftC(note n) {
    short RMBis1 = (n & 1) != 0;
    if (RMBis1) return 0b0000100000000000;
    return n >> 1;
}

note leftShiftC(note n) {
    short LMBis1 = (n & 0b0000100000000000) != 0;
    if (LMBis1) return 1;
    return n << 1;
}

short isPowerOf2(int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

void printBits(note num) {
    unsigned int size = sizeof(note);
    unsigned int maxPow = 1 << (size * 8 - 1);
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < 8; ++j) {
            printf("%u ", num & maxPow ? 1 : 0);
            num = num << 1;
        }
    }
    printf("\n");
}
