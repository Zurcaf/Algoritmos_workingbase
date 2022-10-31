#ifndef PATHS_H
#define PATHS_H

#include "0Main.h"

void graphsAdjs(graph **graphs, char ***tabs, int *lenCount, int maxLen);

int edgeWeight (char *word1, char *word2, int k);

Edge* addEdge(graph *g, int n1, int n2, int wt);

void printAdj(Edge **adj, int lenCount);


//leitura do pals e fazer paths
void makePaths(char *locationStats, int *lenCount, char ***tabs, char *locationPals, int lenMax);

//procurar no diconario indice de uma palavra
int binarySearch(char **tabs, char *nome, int n);


#endif