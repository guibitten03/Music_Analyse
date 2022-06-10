#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "note.h"
#include "algorithms.h"

struct args_t {
	char * filePath;
	long method;
};

typedef struct args_t args;
typedef struct args_t * Args;

void argsShowUsage(char * programName);
void argsParse(Args a, int argc, char ** argv);

void fileGetNotes(FILE * f, note * outNotes);
int fileGetLineSize(FILE * f);

void parseNotes(char * noteSequence, note * notes);

void callMethod(long method, note * original, int M, note * suspect, int T);

int main(int argc, char ** argv) {
	args arguments;
	argsParse(&arguments, argc, argv);

	FILE * inputFile = fopen(arguments.filePath, "r");
	if (NULL == inputFile) {
		fprintf(stderr, "Could not open file: %s\n", arguments.filePath);
		return EXIT_FAILURE;
	}

	short bHasInput = 1;
	do {
		int M, T;
		fscanf(inputFile, "%d %d\n", &M, &T);

		bHasInput = (M != 0) && (T != 0);	

		if (bHasInput) {
			note original[M];
			fileGetNotes(inputFile, original);

			note suspect[T];
			fileGetNotes(inputFile, suspect);

			callMethod(arguments.method, original, M, suspect, T);
		}
	} while (bHasInput);

	fclose(inputFile);

	return EXIT_SUCCESS;
}

void argsParse(Args a, int argc, char ** argv) {
	if (argc < 3) {
		argsShowUsage(argv[0]);
		exit(EXIT_FAILURE);
	}

	a->filePath = argv[1];
	a->method = strtol(argv[2], NULL, 10);
}

void argsShowUsage(char * programName) {
	fprintf(stderr, "Usage: %s <filePath> <Method>\n\n", programName);
	fprintf(stderr, "Available methods:\n"
					"\t1 : Brute force\n"
					"\t2 : KMP\n"
					"\t3 : Boyer-Moore (BMH)\n"
					"\t4 : ShiftAndExato\n");
}

void fileGetNotes(FILE * f, note * outNotes) {
	int lineSz = fileGetLineSize(f);

	char buffer[lineSz + 1];
	fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), f);

	parseNotes(buffer, outNotes);
}

int fileGetLineSize(FILE * f) {
	long filePos = ftell(f);

	char c = '\0';
	int sz = 0;
	while ((c = fgetc(f)) != EOF) {
		sz++;
		if (c == '\n') break;
	}

	fseek(f, filePos, SEEK_SET);

	return sz;
}

void parseNotes(char * noteSequence, note * notes) {
	int i = 0;
	char * noteStr = strtok(noteSequence, " \n");
	do {
		notes[i] = nt_New(noteStr, strlen(noteStr));
		i++;
	} while ((noteStr = strtok(NULL, " \n")) != NULL);
}

void callMethod(long method, note * original, int M, note * suspect, int T) {
	switch (method)
	{
		case 1:
			bruteForce(original, M, suspect, T);
		break;
		
		default:
			fprintf(stderr, "Method doesn't exist or not implemented yet: %ld\n", method);
			exit(EXIT_FAILURE);
	}
}
