#include "getline.h"

// function that reads a line (of arbitrary length)
// from an input source and returns a pointer to
// the array that stores the line read
char *get_line(FILE *f)
{
	int size = 80; // initial size of memory block allocated

	char *linePtr = malloc(size);  // allocate memory block

	if (linePtr != NULL) { // if allocation successful
		int c = EOF;

		// read a line of text and replace newline character
		// with a string terminator character
		int i = 0;
		while ((c = getc(f)) != '\n' && c != EOF && c != ' ') {
			linePtr[i++] = (char) c;
			if (i == size) {
				size *= 2;
				linePtr = realloc(linePtr, size);
			}
		}
		linePtr[i] = '\0';

		// if end-of-file before any characters were read,
		// release the whole buffer
		if (c == EOF && i == 0) {
			free(linePtr);
			linePtr = NULL;
		} else {
			// release unused portion of memory
			linePtr = realloc(linePtr, i+1);
		}
	}

	return linePtr;
}

