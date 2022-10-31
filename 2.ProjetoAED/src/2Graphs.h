#ifndef GRAPHS_H
#define GRAPHS_H
#include "0Main.h"

void makeAdjs(graph *graphs, char **tabs, int lenCount, int maxLen);

int edgeWeight (char *word1, char *word2, int k);

Edge* addEdge(graph *g, int n1, int n2, int wt);

void printAdj(Edge **adj, int lenCount);


//ver no problemas que grafos teremos de inicializar e qual o modo maximo de cada um
void fillGraphs(Problem **palTabs, int maxLen, graph ***gs);

//inicialização de um grafo (alocar e inicializar a 0)
void initGraph(graph **g);

void freeGraph (graph *gs, int maxLen, int lenCount);

#endif