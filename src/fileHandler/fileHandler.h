#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../macros.h"

typedef struct FileHandler FileHandler;

FileHandler *newFileHandler(void);

// handles all file reading
// to counting characters inside
// each file
int promptAndHandleFiles(FileHandler *fh);

int *getCharCount(FileHandler *fh);

#endif