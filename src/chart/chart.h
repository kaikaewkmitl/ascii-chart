#ifndef CHART_H
#define CHART_H

#include <string.h>
#include <stdlib.h>

#include "../macros.h"

#define SORT_ASC 0
#define SORT_DESC 1

typedef struct Chart Chart;

Chart *newChart(void);

int addKeys(Chart *ch, int *charCount);

// sorts by count in ascending
// or descending order
void sortChart(Chart *ch, int order);

void displayChart(Chart *ch);

void deleteChart(Chart *ch);

#endif