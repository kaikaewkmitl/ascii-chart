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

Chart *newChart(void);

int addKeys(Chart *ch, int charCount[]);

// sorts by count in ascending
// or descending order
void sortChart(Chart *ch, eOrder order);

// displays chart with 3 columns:
//     - column 1 is the ASCII characters
//     - column 2 is the count value
//     - column 3 is the bar respresentation of count
void displayChart(Chart *ch, bool isUnicode);

void deleteChart(Chart *ch);

#endif