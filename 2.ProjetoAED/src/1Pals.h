#ifndef PALS_H
#define PALS_H
#include "0Main.h"


void savePals(char *palsLocation, int *nPals, int **palsOrder, Problem ***tabs, int* maxLen);

Problem* initProblem(int size1, int size2);

void addProblem(Problem* p, int size, char* word1, char* word2, int mode, Problem **tabs);

void printPals(Problem **tabs, int maxLe, int nPals, int *palsOrder);


//abertura do ficheiro pals verificar que grafos teremos de inicializar e qual o modo maximo de cada um
void fillGraphs(Problem **palTabs, int maxLen, graph ***gs);

//inicialização de um grafo (alocar e inicializar a 0)
void initGraph(graph **g);


#endif