#ifndef DICIONARIO_H
#define DICIONARIO_H
#include "0Main.h"
//ler, alocar, guardar e ordenar dicinario
void saveDict(char *locationDict, int** lenCount, char ****tabs, int maxLen, bool *palsActivation);

void sortDict(int *lenCount, char ***tabs, int maxLen, bool* palsActivation);
int compare(const void *a, const void *b);

#endif