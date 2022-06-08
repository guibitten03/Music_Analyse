#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "note.h"

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
		fprintf(stdout, "%d %d\n", M, T);

		bHasInput = (M != 0) && (T != 0);	

		if (bHasInput) {
			int lineSz = fileGetNextLineSize(inputFile);

			char lineBuffer[lineSz + 1];
			fgets(lineBuffer, sizeof(lineBuffer) / sizeof(lineBuffer[0]), inputFile);

			printf("Original notes:\n");
			char * note = strtok(lineBuffer, " \n");
			do {
				printf("%s ", note);
			} while ((note = strtok(NULL, " \n")) != NULL);
			printf("\n");

			/* ------------------------------------------------------- */

			lineSz = fileGetNextLineSize(inputFile);

			char suspectBuffer[lineSz + 1];
			fgets(suspectBuffer, sizeof(suspectBuffer) / sizeof(suspectBuffer[0]), inputFile);

			printf("Suspect notes:\n");
			note = strtok(suspectBuffer, " \n");
			do {
				printf("%s ", note);
			} while ((note = strtok(NULL, " \n")) != NULL);
			printf("\n");
		}
	} while (bHasInput);

	fclose(inputFile);

	return EXIT_SUCCESS;
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
