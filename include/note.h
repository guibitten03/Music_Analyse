#ifndef MUSIC_ANALYSE_NOTE_H
#define MUSIC_ANALYSE_NOTE_H
	#include <stdint.h>

	extern const int szAlphabet;

	typedef uint8_t note;

	note nt_New(const char * strNote, int sz);

	note nt_Sharp(note n);
	note nt_Flat(note n);

	int nt_Hash(note n);

	short nt_areSimilars(note a, note b, short * InOutDistance);
#endif
