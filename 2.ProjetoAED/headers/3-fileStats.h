#ifndef FILESTATS_H
#define FILESTATS_H

#include "0-wordsMutation.h"

void getStats(char *locationStats, int *lenCount, char ***tabs, int maxLen, bool *reqPals, char* locationPals);
int binarySearch(char **tabs, char *nome, int n);
char* cutPalsPasteStats(char *locationPals);

#endif