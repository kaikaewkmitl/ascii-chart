#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>

FILE *openFile(char *filename);

void parseFile(FILE *f, int *count);

#endif