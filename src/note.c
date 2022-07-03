#include "note.h"

#include <stdlib.h>
#include <stdio.h>

#define min(a, b) (a <= b ? a : b)
#define max(a, b) (a >= b ? a : b)

const int szAlphabet = 12;

const note C = 0;
const note D = 2;
const note E = 4;
const note F = 5;
const note G = 7;
const note A = 9;
const note B = 11;

static note getNoteFromChar(char c);
static note applyModifier(note n, char modifier);

static short isPowerOf2(int n);

static int distLooping(note a, note b);
static int distStatic(note a, note b);

note nt_New(const char * strNote, int sz) {
	if (sz <= 0) {
		fprintf(stderr, "ERROR: Trying to create a note with size less than or equal to 0.\n");
		exit(EXIT_FAILURE);
	}

	if (sz > 2) {
		fprintf(stderr, "ERROR: Trying to create a note with size greater than 2.\n");
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

static note applyModifier(note n, char mod) {
	switch (mod) {
		case '#': return nt_Sharp(n);

		case 'b': return nt_Flat(n);

		default:
			fprintf(stderr, "Unknown modifier: %c\n", mod);
			exit(EXIT_FAILURE);
	};
}

note nt_Sharp(note n) {
	if (n == B) return C;
	return n + 1;
}

note nt_Flat(note n) {
	if (n == C) return B;
	return n - 1;
}

int nt_Hash(note n) {
	return (int)(n);
}

short nt_areSimilars(note a, note b, short * InOutLastDistance) {
	int lDist = distLooping(a, b);
	int sDist = distStatic(a, b);

	int minDist = min(lDist, sDist);	
	int maxDist = max(lDist, sDist);

	if (*InOutLastDistance == -1) {
		if (isPowerOf2(minDist) || minDist == 0) {
			*InOutLastDistance = minDist;
			return 1;
		}
		if (isPowerOf2(maxDist) || maxDist == 0) {
			*InOutLastDistance = maxDist;
			return 1;
		}
		return 0;
	} else {
		if (minDist == *InOutLastDistance) {
			*InOutLastDistance = minDist;
			return 1;
		}
		if (maxDist == *InOutLastDistance) {
			*InOutLastDistance = maxDist;
			return 1;
		}
		return 0;
	}

	return 0;
}

static int distLooping(note a, note b) {
	note MRN = max(a, b);
	note MLN = min(a, b);

	int dist = (int)(szAlphabet - (nt_Hash(MRN) + 1) + (nt_Hash(MLN) + 1));

	return dist;
}

static int distStatic(note a, note b) {
	note MRN = max(a, b);
	note MLN = min(a, b);

	int dist = (int)(MRN - MLN);

	return dist;
}

short isPowerOf2(int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}
