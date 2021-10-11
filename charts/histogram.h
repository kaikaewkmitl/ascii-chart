#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_LIMIT 25
#define DEFAULT_LONGEST_KEYNAME 4
#define DEFAULT_LONGEST_COUNTDIGIT 5

typedef struct Key
{
    char keyName[CHAR_LIMIT];
    int count;
    float percentage;
} Key;

typedef struct Histogram
{
    char title[CHAR_LIMIT];
    Key *keys;
    int size;
    int longestKeyName;
    int longestCountDigit;
} Histogram;

Histogram *newHistogram(char *title)
{
    Histogram *h = (Histogram *)malloc(sizeof(Histogram));
    strcpy(h->title, title);
    return h;
}

void addKey(Histogram *h, char *keyName, int count)
{
    h->keys = (Key *)realloc(h->keys, h->size++ + 1);
    strcpy(h->keys[h->size - 1].keyName, keyName);
    h->keys[h->size - 1].count = count;
}

int getLongestKeyName(Histogram *h)
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

int getLongestCountDigit(Histogram *h)
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

void printHeader(Histogram *h)
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

void printKeys(Histogram *h)
{
    for (int i = 0; i < h->size; i++)
    {
        printf(" %s ", h->keys[i].keyName);

        int padding = h->longestKeyName - strlen(h->keys[i].keyName);
        printCharNTimes(' ', padding);

        printf("| %d\n", h->keys[i].count);
    }
}

void display(Histogram *h)
{
    h->longestKeyName = getLongestKeyName(h);
    h->longestCountDigit = getLongestCountDigit(h);

    printf("\n%s\n\n", h->title);

    printHeader(h);
    printKeys(h);
}

#endif