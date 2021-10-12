#include "charts/chart.h"

int main()
{
    Chart *h = newChart("MY CHART");
    addKey(h, "first", 1);
    addKey(h, "second", 22);
    addKey(h, "adfdsafdfsfdsafafadfafa", 3);
    addKey(h, "forth", 10);

    display(h);
}