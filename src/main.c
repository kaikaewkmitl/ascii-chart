#include "cmd/cmd.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
#if defined(_WIN32)
    // distinguish between Powershell/Cmd and Bash
    char *shell = getenv("SHELL");
    if (shell == NULL)
    {
        // Powershell/Cmd need this to enable ANSI escape colors
        system("cls");
    }
#endif

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
