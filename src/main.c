#include "chart/chart.h"
#include "fileHandler/fileHandler.h"

#define FILENAME_LIMIT 25

int promptInputs(int *count);

int main(void)
{
    int count[N_ASCII] = {0};
    // if (promptInputs(count) == RETURN_FAILURE)
    // {
    //     return EXIT_FAILURE;
    // }
    while (promptInputs(count) == RETURN_FAILURE)
    {
    };

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

void resetCount(int *count)
{
    for (int i = 0; i < N_ASCII; i++)
    {
        count[i] = 0;
    }
}

int promptInputs(int *count)
{
    int n;
    printf("enter a number of files to read from: ");
    scanf("%d", &n);

    printf("enter name of files separated by space, example, a.txt b.txt c.txt: \n");

    FILE **files = malloc(sizeof(FILE *) * n);
    for (int i = 0; i < n; i++)
    {
        char filename[FILENAME_LIMIT];
        scanf("%s", filename);
        files[i] = newFile(filename);
        if (!files[i])
        {
            resetCount(count);
            fclose(files[i]);
            free(files);
            printf("please try again\n");
            return RETURN_FAILURE;
        }

        countChars(files[i], count);
        fclose(files[i]);
    }

    free(files);
    return RETURN_SUCCESS;
}