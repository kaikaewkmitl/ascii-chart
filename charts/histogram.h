#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <stdio.h>

#define CHAR_LIMIT 25

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
} Histogram;

void display(Histogram h, Key *keys, int n)
{
    h.keys = keys;
    h.size = n;

    printf("\n%s\n\n", h.title);
}

#endif