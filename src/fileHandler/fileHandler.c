#include "fileHandler.h"

#define PREF_PATH "../src/"
#define FILENAME_LIMIT 25

static bool firsttime = true;

FILE *newFile(char *filename);
void countChars(FILE *f, int *count);
int getN(void);
int handleNFiles(int *count, int n);
void resetCount(int *count);

int promptAndHandleFiles(int *count)
{
    if (firsttime)
    {
        firsttime = false;
        printf("%s%s", CLEAR_SCREEN, CURSOR_HOME);
    }

    printf("Enter a %snumber%s of files to read from: ", COLOR_CYAN, COLOR_RESET);
    int n = getN();
    if (n <= 0)
    {
        char msg[CHAR_LIMIT];
        sprintf(msg, "%d is invalid input number\n", n);
        PRINT_ERROR(msg);
        return RETURN_FAILURE;
    }

    printf("\nEnter name of files separated by space or newline;\n");
    printf("example, %sfile1.txt file2.txt file3.txt%s: \n", COLOR_CYAN, COLOR_RESET);
    return handleNFiles(count, n);
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

int getN(void)
{
    char input[CHAR_LIMIT];
    printf("%s", COLOR_CYAN);
    scanf("%s", input);
    printf("%s", COLOR_RESET);
    int n = atoi(input);
    return n;
}

int handleNFiles(int *count, int n)
{
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

void resetCount(int *count)
{
    for (int i = 0; i < N_ASCII; i++)
    {
        count[i] = 0;
    }
}