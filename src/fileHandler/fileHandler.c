#include "fileHandler.h"

#define PREF_PATH "../src/"

struct FileHandler
{
    int n;
    int charCount[N_ASCII];
};

static FileHandler *fh;

static bool firstTime = true;

FILE *newFile(char *filename);
void countChars(FILE *f, int *charCount);
void getN(FileHandler *fh);
int handleNFiles(FileHandler *fh);
void resetCharCount(FileHandler *fh);

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

    printf("Enter a %snumber%s of files to read from: ", COLOR_CYAN, COLOR_RESET);
    getN(fh);
    if (fh->n <= 0)
    {
        char msg[CHAR_LIMIT];
        sprintf(msg, "%d is invalid input number\n", fh->n);
        PRINT_ERROR(msg);
        return RETURN_FAILURE;
    }

    printf("\nEnter name of files separated by space or newline;\n");
    printf("example, %sfile1.txt file2.txt file3.txt%s: \n", COLOR_CYAN, COLOR_RESET);
    return handleNFiles(fh);
}

int *getCharCount(FileHandler *fh)
{
    return fh->charCount;
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

int handleNFiles(FileHandler *fh)
{
    FILE **files = malloc(sizeof(FILE *) * fh->n);
    for (int i = 0; i < fh->n; i++)
    {
        char filename[CHAR_LIMIT];
        printf("%s", COLOR_CYAN);
        scanf("%s", filename);
        printf("%s", COLOR_RESET);
        files[i] = newFile(filename);
        if (!files[i])
        {
            resetCharCount(fh);
            fclose(files[i]);
            free(files);
            PRINT_ERROR("please try again\n");
            return RETURN_FAILURE;
        }

        countChars(files[i], fh->charCount);
        fclose(files[i]);
    }

    free(files);
    return RETURN_SUCCESS;
}

void resetCharCount(FileHandler *fh)
{
    for (int i = 0; i < N_ASCII; i++)
    {
        fh->charCount[i] = 0;
    }
}