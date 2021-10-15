#include "chart/chart.h"
#include "fileHandler/fileHandler.h"

int main(void)
{
    FILE *f = openFile("sample1.txt");
    if (!f)
    {
        return EXIT_FAILURE;
    }

    int count[N_ASCII] = {0};
    countChars(f, count);
    fclose(f);

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