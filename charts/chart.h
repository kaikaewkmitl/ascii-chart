#ifndef CHART_H
#define CHART_H

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

typedef struct Chart
{
    char title[CHAR_LIMIT];
    Key *keys;
    int size;
    int longestKeyName;
    int longestCountDigit;
} Chart;

Chart *newChart(char *title);

void addKey(Chart *h, char *keyName, int count);

void display(Chart *h);

void printHeader(Chart *h);

void printFooter(Chart *h);

void printKeys(Chart *h);

int getLongestKeyName(Chart *h);

int getLongestCountDigit(Chart *h);

void printCharNTimes(char c, int n);

#endif