#include "fileHandler.h"

#define PREF_PATH "../src/"

FILE *openFile(char *filename)
{
    char *tmp = (char *)malloc(strlen(PREF_PATH) + strlen(filename) + 1);
    strcat(strcat(tmp, PREF_PATH), filename);

    FILE *f = fopen(tmp, "r");
    if (!f)
    {
        fprintf(stderr, "failed to open a file %s\n", filename);
    }

    free(tmp);
    return f;
}

void countChars(FILE *f, int *count)
{
    for (int c; (c = fgetc(f)) != EOF;)
    {
        count[c]++;
    }

    rewind(f);
}