#include "cmd.h"

int parseFlags(int argc)
{
    return argc == 1 ? DEFAULT_MODE : WITH_FILES_MODE;
}

int runDefaultMode(void)
{
    FileHandler *fh = newFileHandler();
    if (fh == NULL)
    {
        return RETURN_FAILURE;
    }

    while (promptAndHandleFiles(fh) == RETURN_FAILURE)
        ;

    Chart *ch = newChart();
    if (ch == NULL)
    {
        return RETURN_FAILURE;
    }

    if (addKeys(ch, getCharCount(fh)) == RETURN_FAILURE)
    {
        return RETURN_FAILURE;
    }

    sortChart(ch, Descending);
    displayChart(ch);
    deleteChart(ch);
    return RETURN_SUCCESS;
}

int runWithFilesMode(void)
{
    return RETURN_SUCCESS;
}