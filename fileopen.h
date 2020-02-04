#pragma once
#include <stdio.h>
#include <stdbool.h>

bool openFiles(int argc, const char* argv[]) {
	FILE** pfin;
	FILE** pfout;
	int* n;
	if (argc != 4) { return false; }
	*pfin = fopen(argv[1], "r");

	if (pfin == NULL) {
		fprintf(stderr, "Input file could not be opened");
		return false;
	}
	*pfout = fopen(argv[2], "w");
	if (pfout == NULL) {
		fprintf(stderr, "Output file could not be opened");
		fclose(*pfin);
		return false;
	}
	return false;
}