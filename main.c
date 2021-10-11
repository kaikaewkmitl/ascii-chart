#include "charts/histogram.h"

int main()
{
    Histogram *h = newHistogram("MY CHART");
    addKey(h, "first", 1);
    addKey(h, "second", 22);
    addKey(h, "adfdsafdfsfdsafafadfafa", 3);
    addKey(h, "forth", 123456789);

    display(h);
}