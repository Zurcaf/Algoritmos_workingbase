#ifndef FILESTATS_H
#define FILESTATS_H

#include "0Main.h"

void getStats(char **locationStats, int *lenCount, char ***tabs, char *locationPals, int lenMax);
int binarySearch(char **tabs, char *nome, int n);
void cutPals(char **locationPals);

#endif