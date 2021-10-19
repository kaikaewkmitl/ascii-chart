#include "fileHandler.h"

#define PREF_PATH "../src/"
#define FILENAME_LIMIT 25

FILE *newFile(char *filename);
void countChars(FILE *f, int *count);
void resetCount(int *count);

int promptFiles(int *count)
{
    int n;
    printf("enter a number of files to read from: ");
    scanf("%d", &n);

    printf("enter name of files separated by space or newline\nexample, a.txt b.txt c.txt: \n");

    FILE **files = malloc(sizeof(FILE *) * n);
    for (int i = 0; i < n; i++)
    {
        char filename[FILENAME_LIMIT];
        scanf("%s", filename);
        files[i] = newFile(filename);
        if (!files[i])
        {
            resetCount(count);
            fclose(files[i]);
            free(files);
            printf("please try again\n");
            return RETURN_FAILURE;
        }

        countChars(files[i], count);
        fclose(files[i]);
    }

    free(files);
    return RETURN_SUCCESS;
}

FILE *newFile(char *filename)
{
    char *fullpath = (char *)malloc(strlen(PREF_PATH) + strlen(filename) + 1);
    strcpy(fullpath, PREF_PATH);
    strcat(fullpath, filename);

    FILE *f = fopen(fullpath, "r");
    if (!f)
    {
        fprintf(stderr, "failed to open a file %s\n", filename);
    }

    free(fullpath);
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

void resetCount(int *count)
{
    for (int i = 0; i < N_ASCII; i++)
    {
        count[i] = 0;
    }
}