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

Histogram *newHistogram(char *title);

void addKey(Histogram *h, char *keyName, int count);

void display(Histogram *h);

void printHeader(Histogram *h);

void printFooter(Histogram *h);

void printKeys(Histogram *h);

int getLongestKeyName(Histogram *h);

int getLongestCountDigit(Histogram *h);

void printCharNTimes(char c, int n);

#endif