#include "fileHandler.h"

#define PREF_PATH "../src/"

struct FileHandler
{
    int charCount[N_ASCII];

    // number of files
    // to read from
    int n;
};

static FileHandler *fh;

static bool firstTime = true;

FILE *newFile(char *filename);
void countChars(FILE *f, int *charCount);
void getN(FileHandler *fh);
int handleFiles(FileHandler *fh);
void resetCharCount(int *charCount);

FileHandler *newFileHandler(void)
{
    FileHandler *fh = (FileHandler *)malloc(sizeof(FileHandler));
    if (fh == NULL)
    {
        PRINT_ERROR("failed to allocate a new FileHandler\n");
        return NULL;
    }

    resetCharCount(fh);
    return fh;
}

int promptAndHandleFiles(FileHandler *fh)
{
    if (firstTime)
    {
        firstTime = false;
        printf("%s%s", CLEAR_SCREEN, CURSOR_HOME);
    }

    printf("Enter a %s%snumber%s of files to read from: ", COLOR_CYAN, BOLD_TEXT, COLOR_RESET);
    getN(fh);
    if (fh->n <= 0)
    {
        char msg[CHAR_LIMIT];
        sprintf(msg, "%d is invalid input number\n", fh->n);
        PRINT_ERROR(msg);
        return RETURN_FAILURE;
    }

    printf("\nEnter name of files separated by space or newline;\n");
    printf("example, %s%sfile1.txt file2.txt file3.txt%s: \n", COLOR_CYAN, BOLD_TEXT, COLOR_RESET);
    return handleFiles(fh);
}

int *getCharCount(FileHandler *fh)
{
    return fh->charCount;
}

FILE *newFile(char *filename)
{
    char *fullpath = (char *)malloc(strlen(PREF_PATH) + strlen(filename) + 1);
    if (fullpath == NULL)
    {
        PRINT_ERROR("failed to allocate a file path\n");
        return NULL;
    }

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

void countChars(FILE *f, int *charCount)
{
    for (int c; (c = fgetc(f)) != EOF;)
    {
        charCount[c]++;
    }

    rewind(f);
}

void getN(FileHandler *fh)
{
    char input[CHAR_LIMIT];
    printf("%s", COLOR_CYAN);
    scanf("%s", input);
    printf("%s", COLOR_RESET);
    int n = atoi(input);
    fh->n = n;
}

int handleFiles(FileHandler *fh)
{
    for (int i = 0; i < fh->n; i++)
    {
        char filename[CHAR_LIMIT];
        printf("%s", COLOR_CYAN);
        scanf("%s", filename);
        printf("%s", COLOR_RESET);
        FILE *f = newFile(filename);
        if (f == NULL)
        {
            resetCharCount(fh->charCount);
            PRINT_ERROR("please try again\n");
            return RETURN_FAILURE;
        }

        countChars(f, fh->charCount);
        fclose(f);
    }

    return RETURN_SUCCESS;
}

void resetCharCount(int *charCount)
{
    for (int i = 0; i < N_ASCII; i++)
    {
        charCount[i] = 0;
    }
}