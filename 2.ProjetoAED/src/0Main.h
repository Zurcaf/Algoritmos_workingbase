#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#define DICT_EXT ".dict"
#define PALS_EXT ".pals"
#define PATHS_EXT ".paths"
#define STATS_EXT ".stats"
#define WORD_LEN_MAX 70
#define EXT_NAME_MAX 40
#define LINE_MAX 1000


typedef struct graph
{
    int vertices, maxMode;
    int **adj; 
}graph;

#include "1Dicionario.h"
#include "2Paths.h"

//verificações dos argumentos (quantidade e extensões)
void argsCheck(int argc);


void memoryCheck(void *ptr);


void fileCheck(FILE *filePointer, char *fileName);

//Verficação das exenções dos ficheiros
void dictAndPalsCheck(char* argv[]);

//alocação de memoria para cada um dos nomes do ficheiro
void dictAndPalsAloc(char *argv[], char **dictLocation, char **palsLocation);

//abertura do ficheiro pals verificar que grafos teremos de inicializar e qual o modo maximo de cada um
void fillGraphs(char *palsLocation, int *maxLen, graph ***gs);

//inicialização de um grafo (alocar e inicializar a 0)
void initGraph(graph **g);

//libertação de toda a memoria alocada
void memoryFree(graph **gs, int *lenCount, char ***tabs, int maxLen, char *statsLocation, char *dictLocation, char *palsLocation);

//retirar pals do nome do ficheiro
void cutPals(char **locationPals);

//alocar memoria para o ficheiro de paths
void alocPaths(char **locationStats, char *locationPals);


#endif