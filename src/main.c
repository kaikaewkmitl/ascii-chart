#include "cmd/cmd.h"
#include "fileHandler/fileHandler.h"
#include "chart/chart.h"

int main(int argc, char **argv)
{
    printf("%s%s", CLEAR_SCREEN, CURSOR_HOME);

    if (parseFlags(argc) == DEFAULT_MODE)
    {
        if (runDefaultMode() == RETURN_FAILURE)
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        runWithFilesMode();
    }

    return EXIT_SUCCESS;
}
