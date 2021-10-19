#include "chart/chart.h"
#include "fileHandler/fileHandler.h"

int main(void)
{
    int count[N_ASCII] = {0};

    while (promptFiles(count) == RETURN_FAILURE)
        ;

    Chart *ch = newChart("MY CHART");
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
