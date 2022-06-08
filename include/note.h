#ifndef MUSIC_ANALYSE_NOTE_H
#define MUSIC_ANALYSE_NOTE_H
	#include <stdint.h>

	typedef uint16_t note;

	extern const note C;
	extern const note D;
	extern const note E;
	extern const note F;
	extern const note G;
	extern const note A;
	extern const note B;

	note nt_New(const char * strNote, int sz);

	note nt_Sharp(note n);
	note nt_Flat(note n);

	short nt_areSimilars(note a, note b, short * InOutDistance);
#endif
