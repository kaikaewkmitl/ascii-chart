#include "cmd.h"

#define F_FLAG "-f"
#define H_FLAG "-h"

eMode parseFlags(int argc, char **argv)
{
    if (argc == 1)
    {
        return DefaultMode;
    }

    if (strcmp(F_FLAG, argv[1]) == 0)
    {
        return WithFilesMode;
    }

    if (strcmp(H_FLAG, argv[1]) == 0)
    {
        return HelpMode;
    }

    return UnknownCmd;
}

int runDefaultMode(int charCount[])
{
    FileHandler *fh = newFileHandler();
    if (fh == NULL)
    {
        return RETURN_FAILURE;
    }

    while (promptAndHandleFiles(fh) == RETURN_FAILURE)
        ;

    memcpy(charCount, getCharCount(fh), sizeof(int) * N_ASCII);
    return RETURN_SUCCESS;
}

int runWithFilesMode(int argc, char **argv, int charCount[])
{
    if (argc == 2)
    {
        PRINT_ERROR("no input files\n");
        return RETURN_FAILURE;
    }

    for (int i = 2; i < argc; i++)
    {
        FILE *f = newFile(argv[i]);
        if (f == NULL)
        {
            return RETURN_FAILURE;
        }

        countChars(f, charCount);
        fclose(f);
    }

    return RETURN_SUCCESS;
}

void runHelpMode(char **argv)
{
    printf("ASCII Chart Generator\n");
    printf("KMITL's C-programming project\n\n");
    printf("Usage: %s [%s files...]\n\n", argv[0], F_FLAG);
    printf("Example: %s %s file1.txt file2.txt\n\n", argv[0], F_FLAG);
    printf("ASCII Chart Generator counts ASCII characters from files provided then generates a chart displaying counts of each character\n");
}

void runUnknownCmd(int argc, char **argv)
{
    char msg[CHAR_LIMIT] = "";
    for (int i = 0; i < argc; i++)
    {
        strcat(msg, argv[i]);
        if (i < argc - 1)
        {
            strcat(msg, " ");
        }
    }

    strcat(msg, ": unknown command\n");
    PRINT_ERROR(msg);
    printf("Try '%s %s' for help\n", argv[0], H_FLAG);
}