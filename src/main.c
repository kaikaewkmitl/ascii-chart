#include "cmd/cmd.h"

int main(int argc, char **argv)
{
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
        break;

    case UnknownCmd:
        runUnknownCmd(argc, argv);
        break;
    }

    return EXIT_SUCCESS;
}
