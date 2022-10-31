#ifndef PALS_H
#define PALS_H
#include "0Main.h"


void savePals(char *palsLocation, int *nPals, int **palsOrder, Problem ***tabs, int* maxLen);

Problem* initProblem(int size1, int size2);

void addProblem(Problem* p, int size, char* word1, char* word2, int mode, Problem **tabs);

void printPals(Problem **tabs, int maxLe, int nPals, int *palsOrder);




#endif