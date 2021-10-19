#include "fileHandler/fileHandler.h"
#include "chart/chart.h"

int main(void)
{
    int count[N_ASCII] = {0};

    while (promptAndHandleFiles(count) == RETURN_FAILURE)
        ;

    Chart *ch = newChart();
    if (!ch)
    {
        return EXIT_FAILURE;
    }

    if (addKeys(ch, count) == RETURN_FAILURE)
    {
        return EXIT_FAILURE;
    }

    sortChart(ch, Descending);
    displayChart(ch);
    deleteChart(ch);
    return EXIT_SUCCESS;
}
