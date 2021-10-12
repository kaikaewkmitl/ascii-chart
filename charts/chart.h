#ifndef CHART_H
#define CHART_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Chart Chart;

Chart *newChart(char *title);

void addKey(Chart *ch, char *keyName, int count);

void display(Chart *ch);

#endif