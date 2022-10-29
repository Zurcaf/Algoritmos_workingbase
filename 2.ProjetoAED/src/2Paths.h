#ifndef PATHS_H
#define PATHS_H

#include "0Main.h"

//leitura do pals e fazer paths
void makePaths(char *locationStats, int *lenCount, char ***tabs, char *locationPals, int lenMax);

//procurar no diconario indice de uma palavra
int binarySearch(char **tabs, char *nome, int n);


#endif