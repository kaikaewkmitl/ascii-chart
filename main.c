#include "charts/chart.h"

int main()
{
    Chart *ch = newChart("MY CHART");

    addKey(ch, "first", 1);
    addKey(ch, "second", 22);
    addKey(ch, "adfdsafdfsfdsafafadfafa", 3);
    addKey(ch, "forth", 10);

    sort(ch, Descending);

    display(ch);
}