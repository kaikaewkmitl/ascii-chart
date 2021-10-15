#include "chart/chart.h"
#include "fileHandler/fileHandler.h"

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

    for (int i = 0; i < 128; i++)
    {
        if (freq[i] > 0)
        {
            switch (i)
            {
            case '\n':
                if (addKey(ch, "\\n", freq[i]) == RETURN_FAILURE)
                {
                    return EXIT_FAILURE;
                }
                break;
            case ' ':
                if (addKey(ch, "space", freq[i]) == RETURN_FAILURE)
                {
                    return EXIT_FAILURE;
                }
                break;
            case '\t':
                if (addKey(ch, "\\t", freq[i]) == RETURN_FAILURE)
                {
                    return EXIT_FAILURE;
                }
                break;
            default:
            {
                char c[2] = {i, 0};
                if (addKey(ch, c, freq[i]) == RETURN_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }
            }
        }
    }

    sortChart(ch, Descending);
    displayChart(ch);
    return EXIT_SUCCESS;
}