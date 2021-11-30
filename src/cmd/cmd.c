#include "cmd.h"

#define F_FLAG "-f"
#define H_FLAG "-h"
#define ASC_FLAG "--asc"
#define U_FLAG "-u"

static int charCount[N_ASCII] = {0};

// generate chart in descending fashion by default
static bool isDesc = true;
static bool isUnicode = false;

int generateChart(void);

eMode parseFlags(int argc, char **argv)
{
    bool hasHFlag = false, hasFFlag = false;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(H_FLAG, argv[i]) == 0)
        {
            hasHFlag = true;
        }
        else if (strcmp(F_FLAG, argv[i]) == 0)
        {
            hasFFlag = true;
        }
        else if (strcmp(ASC_FLAG, argv[i]) == 0)
        {
            isDesc = false;
        }
        else if (strcmp(U_FLAG, argv[i]) == 0)
        {
            isUnicode = true;
        }
        else if (argv[i][0] == '-')
        {
            return UnknownCmd;
        }
    }

    if (hasHFlag)
    {
        return HelpMode;
    }

    if (hasFFlag)
    {
        return WithFilesMode;
    }

    return DefaultMode;
}

int runDefaultMode()
{
    printf("%s%s", CLEAR_SCREEN, CURSOR_HOME);
    printf("%s%sASCII Chart Generator%s\n\n", COLOR_GREEN, BOLD_TEXT, COLOR_RESET);

    FileHandler *fh = newFileHandler();
    if (fh == NULL)
    {
        return RETURN_FAILURE;
    }

    while (promptAndHandleFiles(fh) == RETURN_FAILURE)
        ;

    // copy contents of fh->charCount to global charCount
    memcpy(charCount, getCharCount(fh), sizeof(int) * N_ASCII);
    deleteFileHandler(fh);
    return generateChart();
}

int runWithFilesMode(int argc, char **argv)
{
    int i = 1;
    for (; i < argc && argv[i][0] == '-'; i++)
        ;

    if (i == argc)
    {
        PRINT_ERROR("no input files\n");
        return RETURN_FAILURE;
    }

    for (; i < argc && argv[i][0] != '-'; i++)
    {
        FILE *f = newFile(argv[i]);
        if (f == NULL)
        {
            return RETURN_FAILURE;
        }

        countChars(f, charCount);
        fclose(f);
    }

    return generateChart();
}

void runHelpMode(char **argv)
{
    printf("ASCII Chart Generator\n");
    printf("KMITL's C-programming project\n\n");
    printf("Usage: %s [%s files...] [%s]\n\n", argv[0], F_FLAG, ASC_FLAG);
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

int generateChart(void)
{
    Chart *ch = newChart();
    if (ch == NULL)
    {
        return RETURN_FAILURE;
    }

    if (addKeys(ch, charCount) == RETURN_FAILURE)
    {
        return RETURN_FAILURE;
    }

    if (isDesc)
    {
        sortChart(ch, Descending);
    }
    else
    {
        sortChart(ch, Ascending);
    }

    displayChart(ch, isUnicode);
    deleteChart(ch);
    return RETURN_SUCCESS;
}