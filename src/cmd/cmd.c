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

    return Unknown;
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