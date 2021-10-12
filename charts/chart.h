#ifndef CHART_H
#define CHART_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Chart Chart;

typedef enum eOrder
{
    Ascending,
    Descending,
} eOrder;

Chart *newChart(char *title);

void addKey(Chart *ch, char *keyName, int count);

void display(Chart *ch);

// sort keys in ascending or
// descending order
void sort(Chart *ch, eOrder order);

#endif