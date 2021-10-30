#include "cmd/cmd.h"

int main(int argc, char **argv)
{
    int charCount[N_ASCII] = {0};

    eMode mode = parseFlags(argc, argv);
    switch (mode)
    {
    case DefaultMode:
        if (runDefaultMode() == RETURN_FAILURE)
        {
            return EXIT_FAILURE;
        }

        break;

    case WithFilesMode:
        if (runWithFilesMode(argc, argv) == RETURN_FAILURE)
        {
            return EXIT_FAILURE;
        }

        break;

    case HelpMode:
        runHelpMode(argv);
        return EXIT_SUCCESS;

    case UnknownCmd:
        runUnknownCmd(argc, argv);
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
