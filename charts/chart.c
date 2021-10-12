#include "chart.h"

Chart *newChart(char *title)
{
    Chart *h = (Chart *)malloc(sizeof(Chart));
    strcpy(h->title, title);
    return h;
}

void addKey(Chart *h, char *keyName, int count)
{
    h->keys = (Key *)realloc(h->keys, h->size++ + 1);
    strcpy(h->keys[h->size - 1].keyName, keyName);
    h->keys[h->size - 1].count = count;
}

int getLongestKeyName(Chart *h)
{
    int longest = DEFAULT_LONGEST_KEYNAME;

    for (int i = 0; i < h->size; i++)
    {
        int len = strlen(h->keys[i].keyName);
        if (longest < len)
        {
            longest = len;
        }
    }

    return longest;
}

int getLongestCountDigit(Chart *h)
{
    int longest = DEFAULT_LONGEST_COUNTDIGIT;

    for (int i = 0; i < h->size; i++)
    {
        int len = 0, c = h->keys[i].count;
        while (c != 0)
        {
            c /= 10;
            len++;
        }

        if (longest < len)
        {
            longest = len;
        }
    }

    return longest;
}

void printCharNTimes(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}

void printHeader(Chart *h)
{
    printf(" Keys ");

    int padding = h->longestKeyName - DEFAULT_LONGEST_KEYNAME;
    printCharNTimes(' ', padding);

    printf("| Count \n");

    printCharNTimes('-', h->longestKeyName + 2);
    printf("+");
    printCharNTimes('-', h->longestCountDigit + 2);
    printf("\n");
}

void printFooter(Chart *h)
{
    printCharNTimes('-', h->longestKeyName + 2);
    printf("+");
    printCharNTimes('-', h->longestCountDigit + 2);
    printf("\n");
}

void printKeys(Chart *h)
{
    for (int i = 0; i < h->size; i++)
    {
        printf(" %s ", h->keys[i].keyName);

        int padding = h->longestKeyName - strlen(h->keys[i].keyName);
        printCharNTimes(' ', padding);

        printf("| %d\n", h->keys[i].count);
    }
}

void display(Chart *h)
{
    h->longestKeyName = getLongestKeyName(h);
    h->longestCountDigit = getLongestCountDigit(h);

    printf("\n %s\n\n", h->title);

    printHeader(h);
    printKeys(h);
    printFooter(h);
}