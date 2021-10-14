#include "fileHandler.h"

FILE *openFile(char *filename)
{
    FILE *f = fopen(filename, "r");
    return f;
}

void parseFile(FILE *f, int freq[])
{
    for (int c; (c = fgetc(f)) != EOF;)
    {
        freq[c]++;
    }
}