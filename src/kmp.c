#include "kmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern FILE * outputFile;

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

static void KMP_FindSupectPattern(NStack s, note * suspect, int T, int * occurrencePos);
static void KMP_TextToStack(NStack s, note * text, int M);
static int * KMP_Preprocessing (note * suspect, int T);
static note * KMP_SortDescending (note * original_Text, int size);

void KMP(note * original, int M, note * suspect, int T) {
	#ifdef TIMING
		timing t;
		t_Start(&t);
	#endif
	NStack s = ns_New();

	note * invertText = KMP_SortDescending(original, M);

	KMP_TextToStack(s, invertText, M);

	int * occurrencePos = KMP_Preprocessing(suspect, T);

	KMP_FindSupectPattern(s, suspect, T, occurrencePos);

	free(occurrencePos);
	free(invertText);
	ns_Free(s);
	#ifdef TIMING
            t_Finalize(&t);
            t_Print(&t, __func__, n, m);
	#endif
}

static void KMP_FindSupectPattern(NStack s, note * suspect, int T, int * occurrencePos) {
	int suspectNote = 0, stackSize = s->sz;
	short lastDistance = -1; 

	while (s->sz != 0) {
		note poppedItem = ns_Pop(s);

		if (nt_areSimilars(poppedItem, suspect[suspectNote], &lastDistance)) {
			suspectNote++;
			if (suspectNote == T) {
				int indexOfOccurrence = (stackSize - s->sz) - suspectNote;
				fprintf(outputFile, "S %d\n", indexOfOccurrence);
				break;
			}
			continue;
		} else {
			lastDistance = -1;
			while (suspectNote != 0) {
				int currentPosition = suspectNote - 1;
				suspectNote = occurrencePos[currentPosition];

				if (nt_areSimilars(poppedItem, suspect[suspectNote], &lastDistance)) {
					suspectNote++;
					break;
				}
			}
		}

		if (s->sz == 0) {
			fprintf(outputFile, "N\n");
			return;
		}
	}
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
	int * occurrencies = (int *) malloc(sizeof(int) * T);

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
