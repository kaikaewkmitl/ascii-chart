#include "fileHandler.h"

#define PREF_PATH "../src/"
#define FILENAME_LIMIT 25

FILE *newFile(char *filename);
void countChars(FILE *f, int *count);
void resetCount(int *count);

int promptFiles(int *count)
{
    int n;
    printf("enter a %snumber%s of files to read from: ", COLOR_CYAN, COLOR_RESET);
    printf("%s", COLOR_CYAN);
    scanf("%d", &n);
    printf("%s", COLOR_RESET);

    if (n <= 0)
    {
        char msg[CHAR_LIMIT];
        sprintf(msg, "%d is invalid input number\n", n);
        PRINT_ERROR(msg);
        return RETURN_FAILURE;
    }

    printf("enter name of files separated by space or newline\nexample, %sa.txt b.txt c.txt%s: \n", COLOR_CYAN, COLOR_RESET);

    FILE **files = malloc(sizeof(FILE *) * n);
    for (int i = 0; i < n; i++)
    {
        char filename[FILENAME_LIMIT];
        printf("%s", COLOR_CYAN);
        scanf("%s", filename);
        printf("%s", COLOR_RESET);
        files[i] = newFile(filename);
        if (!files[i])
        {
            resetCount(count);
            fclose(files[i]);
            free(files);
            PRINT_ERROR("please try again\n");
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
        char msg[CHAR_LIMIT];
        sprintf(msg, "failed to open a file %s\n", filename);
        PRINT_ERROR(msg);
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