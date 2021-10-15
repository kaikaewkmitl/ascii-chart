#include "chart/chart.h"
#include "fileHandler/fileHandler.h"

#define N_ASCII 128

int addKeysToChart(Chart *ch, int *count);

int main(void)
{
    FILE *f = openFile("../src/sample1.txt");
    if (!f)
    {
        return EXIT_FAILURE;
    }

    int count[N_ASCII] = {0};
    parseFile(f, count);

    Chart *ch = newChart("MY CHART");
    if (!ch)
    {
        return EXIT_FAILURE;
    }

    if (addKeysToChart(ch, count) == RETURN_FAILURE)
    {
        return EXIT_FAILURE;
    }

    sortChart(ch, Descending);
    displayChart(ch);
    return EXIT_SUCCESS;
}

int addKeysToChart(Chart *ch, int *count)
{
    for (int i = 0; i < N_ASCII; i++)
    {
        if (count[i] > 0)
        {
            switch (i)
            {
            case '\n':
                if (addKey(ch, "\\n", count[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            case ' ':
                if (addKey(ch, "space", count[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            case '\t':
                if (addKey(ch, "\\t", count[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            default:
            {
                char keyname[2] = {i, 0};
                if (addKey(ch, keyname, count[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
            }
            }
        }
    }

    return RETURN_SUCCESS;
}