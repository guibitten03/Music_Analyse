#include "note.h"

#include <stdlib.h>
#include <stdio.h>

const note C = 0b0000100000000000;
const note D = 0b0000001000000000;
const note E = 0b0000000010000000;
const note F = 0b0000000001000000;
const note G = 0b0000000000010000;
const note A = 0b0000000000000100;
const note B = 0b0000000000000001;

static note getNoteFromChar(char c);
static note applyModifier(note n, char modifier);

static short checkRight(note a, note b);
static short checkLeft(note a, note b);
static note rightShiftLimited(note n);
static note leftShiftLimited(note n);
static note rightShiftC(note n);
static note leftShiftC(note n);
static short isPowerOf2(int n);

note nt_New(const char * strNote, int sz) {
	if (sz <= 0) {
		fprintf(stderr, "ERROR: sz <= 0.\n");
		exit(EXIT_FAILURE);
	}

	if (sz > 2) {
		fprintf(stderr, "ERROR: sz > 2.\n");
		exit(EXIT_FAILURE);
	}

	note result = 0;

	for (int i = 0; i < sz; i++) {
		char c = strNote[i];
		switch (i) {
			case 0:
				result = getNoteFromChar(c);				
			break;

			case 1:
				result = applyModifier(result, c);
			break;
		}
	}

	return result;
}

static note getNoteFromChar(char c) {
	switch (c) {
		case 'C': return C;

		case 'D': return D;

		case 'E': return E;

		case 'F': return F;

		case 'G': return G;

		case 'A': return A;

		case 'B': return B;
		
		default:
			fprintf(stderr, "Unknown note: %c\n", c);
			exit(EXIT_FAILURE);
	};
}

static note applyModifier(note n, char modifier) {
	switch (modifier) {
		case '#': return nt_Sharp(n);

		case 'b': return nt_Flat(n);

		default:
			fprintf(stderr, "Unknown modifier: %c\n", modifier);
			exit(EXIT_FAILURE);
	};
}

note nt_Sharp(note n) {
	return rightShiftC(n);
}

note nt_Flat(note n) {
	return leftShiftC(n);
}

short nt_areSimilars(note a, note b) {
    short rightResult = checkRight(a, b);
    short leftResult = checkLeft(a, b);
    return rightResult || leftResult;
}

short nt_areEquals(note a, note b) {
	return a == b;
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
