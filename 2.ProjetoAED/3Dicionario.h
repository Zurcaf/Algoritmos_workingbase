#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "0Main.h"

//ler, alocar, guardar e ordenar dicinario
void saveDict(char *locationDict, int** lenCount, char ****tabs, int maxLen, graph **gs);

void sortDict(int *lenCount, char ***tabs, int maxLen, graph **gs);
int compare(const void *a, const void *b);

#endif