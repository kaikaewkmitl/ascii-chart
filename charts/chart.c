#include "chart.h"

char *COLUMNS[N_COLUMNS] = {"Keys", "Count", "Chart"};

Chart *newChart(char *title)
{
    Chart *ch = (Chart *)malloc(sizeof(Chart));
    strcpy(ch->title, title);

    for (int i = 0; i < N_COLUMNS; i++)
    {
        ch->columnWidth[i] = strlen(COLUMNS[i]);
        printf("%d\n", ch->columnWidth[i]);
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
    getLongestKeyName(ch);
    getLongestCountDigit(ch);
    getMaxCount(ch);

    printf("\n %s\n\n", ch->title);

    printHeader(ch);
    printKeys(ch);
    printFooter(ch);
}

void printHeader(Chart *ch)
{
    printf(" Keys ");
    int padding = ch->longestKeyName - strlen(COLUMNS[0]);
    printCharNTimes(' ', padding);

    printf("| Count ");
    padding = ch->longestCountDigit - strlen(COLUMNS[1]);
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
        int padding = ch->longestKeyName - strlen(ch->keys[i].keyName);
        printCharNTimes(' ', padding);

        printf("| %d\n", ch->keys[i].count);
        // int padding = ch->longestCountDigit - strlen
    }
}

void printNewRow(Chart *ch)
{
    if (ch->longestKeyName > strlen(COLUMNS[0]))
    {
        printCharNTimes('-', ch->longestKeyName + 2);
    }
    else
    {
        printCharNTimes('-', strlen(COLUMNS[0]) + 2);
    }

    printf("+");
    if (ch->longestCountDigit > strlen(COLUMNS[1]))
    {
        printCharNTimes('-', ch->longestCountDigit + 2);
    }
    else
    {
        printCharNTimes('-', strlen(COLUMNS[1]) + 2);
    }

    printf("+");
    if (ch->maxCount > strlen(COLUMNS[2]))
    {
        printCharNTimes('-', ch->maxCount + 2);
    }
    else
    {
        printCharNTimes('-', strlen(COLUMNS[2]) + 2);
    }

    printf("\n");
}

void getLongestKeyName(Chart *ch)
{
    int longest = 0;

    for (int i = 0; i < ch->size; i++)
    {
        int len = strlen(ch->keys[i].keyName);
        if (longest < len)
        {
            longest = len;
        }
    }

    ch->longestKeyName = longest;
}

void getLongestCountDigit(Chart *ch)
{
    int longest = 0;

    for (int i = 0; i < ch->size; i++)
    {
        if (longest < ch->keys[i].countDigit)
        {
            longest = ch->keys[i].countDigit;
        }
    }

    ch->longestCountDigit = longest;
}

void getMaxCount(Chart *ch)
{
    int max = 0;
    for (int i = 0; i < ch->size; i++)
    {
        if (max < ch->keys[i].count)
        {
            max = ch->keys[i].count;
        }
    }

    ch->maxCount = max;
}

void printCharNTimes(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}
