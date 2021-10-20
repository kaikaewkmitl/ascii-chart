#include "fileHandler/fileHandler.h"
#include "chart/chart.h"

int main(void)
{
    FileHandler *fh = newFileHandler();
    if (fh == NULL)
    {
        return EXIT_FAILURE;
    }

    while (promptAndHandleFiles(fh) == RETURN_FAILURE)
        ;

    Chart *ch = newChart();
    if (ch == NULL)
    {
        return EXIT_FAILURE;
    }

    if (addKeys(ch, getCharCount(fh)) == RETURN_FAILURE)
    {
        return EXIT_FAILURE;
    }

    sortChart(ch, Descending);
    displayChart(ch);
    deleteChart(ch);
    return EXIT_SUCCESS;
}
