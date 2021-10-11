#include "charts/histogram.h"

int main()
{
    Histogram h = {.title = "MY CHART"};
    Key keys[] = {{"first", 1}, {"second", 22}, {"waitasecondplease", 3}, {"forth", 123456789}};

    display(h, keys, 4);
}