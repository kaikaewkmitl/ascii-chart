#include "chart.h"

char *COLUMNS[N_COLUMNS] = {"Keys", "Count", "Chart"};

Chart *newChart(char *title)
{
    Chart *ch = (Chart *)malloc(sizeof(Chart));
    strcpy(ch->title, title);

    for (int i = 0; i < N_COLUMNS; i++)
    {
        ch->columnWidth[i] = strlen(COLUMNS[i]);
    }
    return ch;
}

void addKey(Chart *ch, char *keyName, int count)
{
    ch->keys = (Key *)realloc(ch->keys, ch->size++ + 1);
    strcpy(ch->keys[ch->size - 1].keyName, keyName);
    ch->keys[ch->size - 1].count = count;

    int digit = 0;
    while (count != 0)
    {
        count /= 10;
        digit++;
    }

    ch->keys[ch->size - 1].countDigit = digit;
}

void display(Chart *ch)
{
    updateColumn1Width(ch);
    updateColumn2Width(ch);
    updateColumn3Width(ch);

    printf("\n %s\n\n", ch->title);

    printHeader(ch);
    printKeys(ch);
    printFooter(ch);
}

void printHeader(Chart *ch)
{
    printf(" Keys ");
    int padding = ch->columnWidth[0] - strlen(COLUMNS[0]);
    printCharNTimes(' ', padding);

    printf("| Count ");
    padding = ch->columnWidth[1] - strlen(COLUMNS[1]);
    printCharNTimes(' ', padding);

    printf("| Chart \n");

    printNewRow(ch);
}

void printFooter(Chart *ch)
{
    printNewRow(ch);
    printf("\n");
}

void printKeys(Chart *ch)
{
    for (int i = 0; i < ch->size; i++)
    {
        printf(" %s ", ch->keys[i].keyName);
        int padding = ch->columnWidth[0] - strlen(ch->keys[i].keyName);
        printCharNTimes(' ', padding);

        printf("| %d ", ch->keys[i].count);
        padding = ch->columnWidth[1] - ch->keys[i].countDigit;
        printCharNTimes(' ', padding);

        printf("| ");
        printCharNTimes('#', ch->keys[i].count);
        printf(" \n");
    }
}

void printNewRow(Chart *ch)
{
    for (int i = 0; i < N_COLUMNS; i++)
    {
        printCharNTimes('-', ch->columnWidth[i] + 2);
        if (i != N_COLUMNS - 1)
        {
            printf("+");
        }
    }

    printf("\n");
}

void updateColumn1Width(Chart *ch)
{
    for (int i = 0; i < ch->size; i++)
    {
        int len = strlen(ch->keys[i].keyName);
        if (ch->columnWidth[0] < len)
        {
            ch->columnWidth[0] = len;
        }
    }
}

void updateColumn2Width(Chart *ch)
{
    for (int i = 0; i < ch->size; i++)
    {
        if (ch->columnWidth[1] < ch->keys[i].countDigit)
        {
            ch->columnWidth[1] = ch->keys[i].countDigit;
        }
    }
}

void updateColumn3Width(Chart *ch)
{
    for (int i = 0; i < ch->size; i++)
    {
        if (ch->columnWidth[2] < ch->keys[i].count)
        {
            ch->columnWidth[2] = ch->keys[i].count;
        }
    }
}

void printCharNTimes(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}
