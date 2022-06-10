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

int fileGetNextLineSize(FILE * f);

void parseNotes(char * line, note * notes);

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
			int lineSz = fileGetNextLineSize(inputFile);

			char originalBuffer[lineSz + 1];
			fgets(originalBuffer, sizeof(originalBuffer) / sizeof(originalBuffer[0]), inputFile);

			note original[M];

			parseNotes(originalBuffer, original);

			lineSz = fileGetNextLineSize(inputFile);

			char suspectBuffer[lineSz + 1];
			fgets(suspectBuffer, sizeof(suspectBuffer) / sizeof(suspectBuffer[0]), inputFile);

			note suspect[T];

			parseNotes(suspectBuffer, suspect);

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

int fileGetNextLineSize(FILE * f) {
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

void parseNotes(char * line, note * notes) {
	int i = 0;
	char * noteStr = strtok(line, " \n");
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
