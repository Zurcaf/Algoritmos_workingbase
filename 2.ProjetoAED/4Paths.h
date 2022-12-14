#ifndef PATHS_H
#define PATHS_H

#include "0Main.h"

//leitura do pals e fazer paths
void makePaths(char *locationStats, int *dicLenCount, char ***dicTabs, int maxLen, Problem **tabs, int nPals, int* palsOrder);

//procurar no diconario indice de uma palavra
int binarySearch(char **tabs, char *nome, int n);



int minDistance(int *dist, bool *sptSet, int nv);
void getPath(int parent[], int j, Path **path );
void dijkstra(Problem *palsTab, int sn, int nv, int end, Edge **adjs);
void printPath(Path *path, char **dictTabs);

#endif