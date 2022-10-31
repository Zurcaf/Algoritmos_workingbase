#include "0Main.h"

void makeAdjs(graph *graph, char **tabs, int lenCount, int maxLen)
{
    int i = 0, j = 0, wtAux = 0, maxModeAux = 0, k=0;

    k = strlen(tabs[0]);

    graph->adj = (Edge **)calloc(lenCount, sizeof(Edge *));
    memoryCheck(graph->adj);

    for (i = 0; i < lenCount; i++)
    {
        for (j = i; j < lenCount; j++)
        {
            wtAux = edgeWeight(tabs[i], tabs[j], k);
            maxModeAux = graph->maxMode * graph->maxMode;
            if (wtAux > maxModeAux)
            {
                continue;
            }
            if (wtAux > 0)
            {
                graph->adj[i] = addEdge(graph, i, j, wtAux);
                graph->adj[j] = addEdge(graph, j, i, wtAux);
            }
            wtAux = 0;
        }
        maxModeAux = 0;
    }
    //printAdj(graph->adj, lenCount);
}

void printAdj(Edge **adj, int lenCount)
{
    int i = 0;
    Edge *aux = NULL;
    for (i = 0; i < lenCount; i++)
    {
        aux = adj[i];
        printf("%d: ", i);
        while (aux != NULL)
        {
            printf("%d(%d) ", aux->n2, aux->wt);
            aux = aux->next;
        }
        printf("\n");
    }
}

int edgeWeight(char *word1, char *word2, int k)
{
    int i = 0, count = 0;

    for (i = 0; i < k; i++)
    {
        if (word1[i] != word2[i])
        {
            count++;
        }
    }

    count *= count;

    return count;
}

Edge *addEdge(graph *g, int n1, int n2, int wt)

{
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    memoryCheck(newEdge);

    newEdge->n2 = n2;
    newEdge->wt = wt;
    newEdge->next = g->adj[n1];
    return newEdge;
}

void fillGraphs(Problem **palsTabs, int maxLen, graph ***gs)
{
    *gs = (graph **)calloc(maxLen, sizeof(graph *));
    memoryCheck(*gs);

    int i=0;
    for(i=0; i< maxLen; i++)
    {
        if(palsTabs[i] != NULL)
        {
            initGraph(&(*gs)[i]);
            if(palsTabs[i]->mode > (*gs)[i]->maxMode)
            {
                (*gs)[i]->maxMode = palsTabs[i]->mode;
            }
        }
    }

}

void initGraph(graph **g)
{
    (*g) = (graph *)malloc(sizeof(graph));
    memoryCheck(*g);

    (*g)->vertices = 0;
    (*g)->maxMode = 0;
    (*g)->adj = NULL;
}

void freeGraph (graph *gs, int maxLen, int lenCount)
{
    int j = 0;
    Edge *aux = NULL, *aux2 = NULL;

    for (j = 0; j < lenCount; j++)
    {
        if(gs->adj[j] != NULL)
        {
            aux = gs->adj[j];
            while (aux != NULL)
            {
                aux2 = aux;
                aux = aux->next;
                free(aux2);
            }
            
        }
    }

    free(gs->adj);
    
    
}
