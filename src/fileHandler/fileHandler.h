#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../macros.h"

typedef struct FileHandler FileHandler;

FileHandler *newFileHandler(void);

// just fopen on r mode with error checking
FILE *newFile(char filename[]);

// handles all files reading and counting
// characters inside each file
int promptAndHandleFiles(FileHandler *fh);

void countChars(FILE *f, int charCount[]);

// returns array of size 128 where each index
// represents an ASCII character with its count
// being the value of array at that index
int *getCharCount(FileHandler *fh);

void deleteFileHandler(FileHandler *fh);

#endif