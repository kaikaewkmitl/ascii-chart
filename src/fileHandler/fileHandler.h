#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// open file for read
FILE *openFile(char *filename);

void countChars(FILE *f, int *count);

#endif