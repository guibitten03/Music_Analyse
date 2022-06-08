#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "note.h"

void BruteForce(note * original, int n, note * suspect, int m);

struct args_t {
	char * filePath;
	long method;
};

typedef struct args_t args;
typedef struct args_t * Args;

void argsShowUsage(char * programName);
void argsParse(Args a, int argc, char ** argv);

int fileGetNextLineSize(FILE * f);

int main(int argc, char ** argv) {
	args arguments;
	argsParse(&arguments, argc, argv);

	printf("filePath: %s | method: %ld\n", arguments.filePath, arguments.method);

	FILE * inputFile = fopen(arguments.filePath, "r");
	if (NULL == inputFile) {
		fprintf(stderr, "Could not open file: %s\n", arguments.filePath);
		return EXIT_FAILURE;
	}

	short bHasInput = 1;
	do {
		int M, T;
		fscanf(inputFile, "%d %d\n", &M, &T);
		//fprintf(stdout, "%d %d\n", M, T);

		bHasInput = (M != 0) && (T != 0);	

		if (bHasInput) {
			int lineSz = fileGetNextLineSize(inputFile);

			char lineBuffer[lineSz + 1];
			fgets(lineBuffer, sizeof(lineBuffer) / sizeof(lineBuffer[0]), inputFile);

			note original[M];

			int i = 0;
			char * noteStr = strtok(lineBuffer, " \n");
			do {
				original[i] = nt_New(noteStr, strlen(noteStr));
				i++;
			} while ((noteStr = strtok(NULL, " \n")) != NULL);

			/* ------------------------------------------------------- */

			lineSz = fileGetNextLineSize(inputFile);

			char suspectBuffer[lineSz + 1];
			fgets(suspectBuffer, sizeof(suspectBuffer) / sizeof(suspectBuffer[0]), inputFile);

			note suspect[T];

			i = 0;
			noteStr = strtok(suspectBuffer, " \n");
			do {
				suspect[i] = nt_New(noteStr, strlen(noteStr));
				i++;
			} while ((noteStr = strtok(NULL, " \n")) != NULL);

			BruteForce(original, M, suspect, T);
		}
	} while (bHasInput);

	fclose(inputFile);

	return EXIT_SUCCESS;
}

void BruteForce(note * original, int n, note * suspect, int m) {
	for (int i = 0; i < n - m + 1; i++) {
		int k = i;
		int j = 0;

		short lastDistance = -1;
		while (nt_areSimilars(original[k], suspect[j], &lastDistance)) {
			k++; j++;
			if (j == m) {
				printf("S %d\n", i);
				return;	
			}
		}
	}
	printf("N\n");
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
