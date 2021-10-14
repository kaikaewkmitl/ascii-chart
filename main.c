#include "chart/chart.h"

int main(void)
{
    Chart *ch = newChart("MY CHART");
    if (!ch)
    {
        return EXIT_FAILURE;
    }

    if (addKey(ch, "first", 1) == RETURN_FAILURE)
    {
        return EXIT_FAILURE;
    }

    addKey(ch, "second", 22);
    addKey(ch, "adfdsafdfsfdsafafadfafa", 3);
    addKey(ch, "forth", 10);

    sortChart(ch, Descending);
    displayChart(ch);
    return EXIT_SUCCESS;
}