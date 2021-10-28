#include "cmd/cmd.h"
#include "chart/chart.h"

int main(int argc, char **argv)
{
    int charCount[N_ASCII] = {0};

    eMode mode = parseFlags(argc, argv);
    switch (mode)
    {
    case DefaultMode:
        if (runDefaultMode(charCount) == RETURN_FAILURE)
        {
            return EXIT_FAILURE;
        }

        break;

    case WithFilesMode:
        if (runWithFilesMode(argc, argv, charCount) == RETURN_FAILURE)
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

    printf("%s%s", CLEAR_SCREEN, CURSOR_HOME);
    printf("%s%sASCII Chart Generator%s\n\n", COLOR_GREEN, BOLD_TEXT, COLOR_RESET);

    Chart *ch = newChart();
    if (ch == NULL)
    {
        return EXIT_FAILURE;
    }

    if (addKeys(ch, charCount) == RETURN_FAILURE)
    {
        return EXIT_FAILURE;
    }

    sortChart(ch, Descending);
    displayChart(ch);
    deleteChart(ch);

    return EXIT_SUCCESS;
}
