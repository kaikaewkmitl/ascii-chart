#ifndef CHART_H
#define CHART_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#define N_ASCII 128

typedef struct Chart Chart;

typedef enum eOrder
{
    Ascending,
    Descending,
} eOrder;

Chart *newChart(char *title);

int addKeys(Chart *ch, int *count);

// sorts by count in ascending
// or descending order
void sortChart(Chart *ch, eOrder order);

void displayChart(Chart *ch);

void deleteChart(Chart *ch);

#endif