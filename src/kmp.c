#include "kmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct note_stack_node_t {
	struct note_stack_node_t * previous;
	note n;
} * NSNode;

typedef struct note_stack_t {
	NSNode top;
	int sz;
} * NStack;

NStack ns_New(void);
note ns_Pop(NStack s);
void ns_Add(NStack s, note n);
void ns_Free(NStack s);

static void KMP_TextToStack(NStack s, note * text, int M);
static int * KMP_Preprocessing (note * suspect, int T);
static note * KMP_SortDescending (note * original_Text, int size);

void KMP(note * original, int M, note * suspect, int T) {
	NStack s = ns_New();

	note * invertText = KMP_SortDescending(original, M);

	KMP_TextToStack(s, invertText, M);

	int * occurrencePos = KMP_Preprocessing(suspect, T);

	int j = 0, stackSize = s->sz;
	short lastDistance = -1; 

	while (s->sz != 0) {
		note poppedItem = ns_Pop(s);
		if (poppedItem == -1) break;

		if (nt_areSimilars(poppedItem, suspect[j], &lastDistance)) {
			j++;
			if (j == T) {
				int indexOfOccurrence = (stackSize - s->sz) - j;
				printf("S %d\n", indexOfOccurrence);
				break;
			}
			continue;
		} else {
			lastDistance = -1;
			while (j != 0) {
				int currentPosition = j - 1;
				j = occurrencePos[currentPosition];

				if (nt_areSimilars(poppedItem, suspect[j], &lastDistance)) {
					j++;
					break;
				}
			}
		}

		if (s->sz == 0) {
			printf("N\n");
		}
	}

	free(occurrencePos);
	free(invertText);
	ns_Free(s);
}

static note * KMP_SortDescending (note * originalText, int size) {
	note * invertText = (note *) malloc(sizeof(note) * size);
	int firstPivot = 0, lastPivot = size - 1;

	while (firstPivot != size) {
		invertText[firstPivot] = originalText[lastPivot];

		firstPivot++;
		lastPivot--;
	}

	return invertText;
}

static int * KMP_Preprocessing (note * suspect, int T) {
	int * occurrencies = (int*) malloc(sizeof(int) * T);

	for (int i = 0; i < T; i++) {
		occurrencies[i] = 0;
	}

	int i = 0, j = 1;
	short lastDistance = -1;

	while (j < T) {
		if (nt_areSimilars(suspect[i], suspect[j], &lastDistance)) {
			i++;
			occurrencies[j] = i;
			j++;
		} else {
			if (i == 0) {
				j++;
			}
			if (i > 0) {
				int aux = i - 1;
				i = occurrencies[aux];
			}
		}
	}

	return occurrencies;

}

static void KMP_TextToStack(NStack s, note * text, int M) {
	for (int i = 0; i < M; i++) {
		ns_Add(s, text[i]);
	}
}

NStack ns_New(void) {
	NStack s = (NStack) malloc(sizeof(struct note_stack_t));
	s->sz = 0;
	return s;
}

note ns_Pop(NStack s) {
	if (s->sz == 0) {
		fputs("ERROR: Trying to pop a note from an empty stack.\n", stderr);
		return -1;
	}

	NSNode popped = s->top;
	NSNode newTop = popped->previous;
	
	note result = popped->n;

	s->sz--;
	s->top = newTop;

	free(popped);

	return result;
}

void ns_Add(NStack s, note n) {
	NSNode new = (NSNode) malloc(sizeof(struct note_stack_node_t));
	new->n = n;

	new->previous = s->top;
	s->top = new;

	s->sz++;
}

void ns_Free(NStack s) {
	while (s->sz > 0) {
		ns_Pop(s);
	}
	free(s);
}
