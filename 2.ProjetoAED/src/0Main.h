#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


#define DICT_EXT ".dict"
#define PALS_EXT ".pals"
#define PATHS_EXT ".paths"
#define STATS_EXT ".stats"
#define WORD_LEN_MAX 70
#define EXT_NAME_MAX 40
#define LINE_MAX 1000

typedef struct _edge Edge;

typedef struct _edge
{
    int n2;
    int wt;
    Edge *next;
    Edge *previous;
} Edge;


typedef struct graph
{
    int vertices, maxMode;
    Edge **adj; 
}graph;

typedef struct _path Path;

typedef struct _path
{
    int n2;
    Path *previous;
    Path *next;
} Path;

typedef struct problem_ Problem;

struct problem_{
    char* word1;
    char* word2;
    int mode;
    int indexOrder;
    int pathDist;
    Path *path;
    Problem *next;
};


#include "1Pals.h"
#include "2Graphs.h"
#include "3Dicionario.h"
#include "4Paths.h"

//libertação de toda a memoria alocada
void freeOtherMemory(int maxLen, graph **gs, int *palsOrder, int *dictLenCount, char *statsLocation, char *dictLocation, char *palsLocation);

void freeDict(char ***tabs, int *lenCount, int maxLen);

void freePals (Problem **palsTabs, int maxLen);

//verificações dos argumentos (quantidade e extensões)
void argsCheck(int argc);

//verificação de memoria alocada
void memoryCheck(void *ptr);


void fileCheck(FILE *filePointer, char *fileName);

//Verficação das exenções dos ficheiros
void dictAndPalsCheck(char* argv[]);

//alocação de memoria para cada um dos nomes do ficheiro
void dictAndPalsAloc(char *argv[], char **dictLocation, char **palsLocation);



//retirar pals do nome do ficheiro
void cutPals(char **locationPals);

//alocar memoria para o ficheiro de paths
void alocPaths(char **locationStats, char *locationPals);



#endif