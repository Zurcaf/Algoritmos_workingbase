#ifndef PATHS_H
#define PATHS_H

#include "0Main.h"

//leitura do pals e fazer paths
void makePaths(char *locationStats, int *lenCount, char ***tabs, char *locationPals, int lenMax);

//procurar no diconario indice de uma palavra
int binarySearch(char **tabs, char *nome, int n);



int minDistance(int *dist, bool *sptSet, int nv);
void getPath(int parent[], int j, Path **path );
void dijkstra(Problem *palsTab, int sn, int nv, int end, Edge **adjs);

#endif