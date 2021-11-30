#ifndef CHART_H
#define CHART_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../macros.h"

typedef struct Chart Chart;

typedef enum eOrder
{
    Ascending,
    Descending,
} eOrder;

int generateChart(void);

Chart *newChart(void);

int addKeys(Chart *ch, int charCount[]);

// sorts by count in ascending
// or descending order
void sortChart(Chart *ch, eOrder order);

void displayChart(Chart *ch, bool isUnicode);

void deleteChart(Chart *ch);

#endif