#include "fileHandler.h"

FILE *openFile(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "failed to open a file %s\n", filename);
    }

    return f;
}

void parseFile(FILE *f, int *count)
{
    for (int c; (c = fgetc(f)) != EOF;)
    {
        count[c]++;
    }
}