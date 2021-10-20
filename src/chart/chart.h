#ifndef CHART_H
#define CHART_H

#include <string.h>
#include <stdlib.h>

#include "../macros.h"

typedef struct Chart Chart;

typedef enum eOrder
{
    Ascending,
    Descending,
} eOrder;

Chart *newChart(void);

int addKeys(Chart *ch, int *count);

// sorts by count in ascending
// or descending order
void sortChart(Chart *ch, eOrder order);

void displayChart(Chart *ch);

void deleteChart(Chart *ch);

#endif