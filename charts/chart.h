#ifndef CHART_H
#define CHART_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_LIMIT 25
#define N_COLUMNS 3

typedef struct Key
{
    char keyName[CHAR_LIMIT];
    int count;
    int countDigit;
    float percentage;
} Key;

typedef struct Chart
{
    char title[CHAR_LIMIT];
    Key *keys;
    int size;
    int columnWidth[N_COLUMNS];
} Chart;

Chart *newChart(char *title);

void addKey(Chart *ch, char *keyName, int count);

void display(Chart *ch);

void printHeader(Chart *ch);

void printFooter(Chart *ch);

void printKeys(Chart *ch);

void printNewRow(Chart *ch);

void updateColumn1Width(Chart *ch);

void updateColumn2Width(Chart *ch);

void updateColumn3Width(Chart *ch);

void printCharNTimes(char c, int n);

#endif