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

	note * invert_Text = KMP_SortDescending(original, M);

	KMP_TextToStack(s, invert_Text, M);

	int * occurrence_pos = KMP_Preprocessing(suspect, T);
	short last_distance = -1;

	int j = 0, stack_Size = s->sz;

	// for (int i = 0; i < T; i++) {
	// 	printf("%d\n", occurrence_pos[i]);
	// }

	while (s->sz != 0) { 
		note popped_Item = ns_Pop(s);
		if (popped_Item == -1) break;

		if (nt_areSimilars(popped_Item, suspect[j], &last_distance)) {
			j++;
			if (j == T) {
				int indexOfOccurrence = (stack_Size - s->sz) - j;
				printf("S %d\n", indexOfOccurrence);
				break;
			}
			continue;
		} else {
			while (j != 0) {
				int current_Position = j - 1;
				j = occurrence_pos[current_Position];
				if (nt_areSimilars(popped_Item, suspect[j], &last_distance)) {
					j++;
					break;
				}
			}
		}

		if (s->sz == 0) {
			printf("N\n");
		}
	}

	free(occurrence_pos);
	free(invert_Text);
	ns_Free(s);
}

static note * KMP_SortDescending (note * original_Text, int size) {
	note * invert_Text = (note *) malloc(sizeof(note) * size);
	int first_Pivot = 0, last_Pivot = size - 1;

	while (first_Pivot != size) {
		invert_Text[first_Pivot] = original_Text[last_Pivot];

		first_Pivot++;
		last_Pivot--;
	}

	return invert_Text;
}

static int * KMP_Preprocessing (note * suspect, int T) {
	int * occurrencies = (int*) malloc(sizeof(int) * T);

	for (int i = 0; i < T; i++) {
		occurrencies[i] = 0;
	}

	int i = 0, j = 1;
	short last_distance = -1;

	while (j < T) {
		if (nt_areSimilars(suspect[i], suspect[j], &last_distance)) {
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
