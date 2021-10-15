#include "chart/chart.h"
#include "fileHandler/fileHandler.h"
#include "helper/helper.h"

int main(void)
{
    FILE *f = openFile("../src/sample1.txt");
    if (!f)
    {
        return EXIT_FAILURE;
    }

    int freq[128] = {0};
    parseFile(f, freq);

    Chart *ch = newChart("MY CHART");
    if (!ch)
    {
        return EXIT_FAILURE;
    }

    if (charCount(ch, freq) == RETURN_FAILURE)
    {
        return EXIT_FAILURE;
    }

    sortChart(ch, Descending);
    displayChart(ch);
    return EXIT_SUCCESS;
}