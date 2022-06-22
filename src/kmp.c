#include "kmp.h"

#include <stdio.h>
#include <stdlib.h>

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

void ns_TextToStack(NStack s, note * text, int M);

int * km_Preprocessing (note * suspect, int T);

void KMP(note * original, int M, note * suspect, int T) {
	NStack s = ns_New();

	ns_TextToStack(s, original, M);

	int * occurrence_pos = km_Preprocessing(suspect, T);

	for (int i = 0; i < T; i++) {
		printf("%d\n", occurrence_pos[i]);
	}

	int i = 0, j = 0;
	while (j < M) {
		
		if () {

		}
	}

	ns_Free(s);
}

int * km_Preprocessing (note * suspect, int T) {
	int * occurrencies = (int*) malloc(sizeof(int) * T);

	for (int i = 0; i < T; i++) {
		occurrencies[i] = 0;
	}

	int i = 0, j = 1;

	while (j < T) {

		if ((suspect[i] != suspect[j]) && i == 0) {
			j++;
		} else if ((suspect[i] != suspect[j]) && i > 0) {
			int aux = i - 1;
			i = occurrencies[aux];
		}
		
		if (suspect[i] == suspect[j]) {
			i++;
			occurrencies[j] = i;
			j++;
		}
	}

	return occurrencies;

}

void ns_TextToStack(NStack s, note * text, int M) {
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
		exit(EXIT_FAILURE);
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
