#include "0Main.h"

void makePaths(char *locationStats, int *lenCount, char ***tabs, char *locationPals, int lenMax)
{
    FILE *palsPointer = NULL, *statsPointer = NULL;
    char word1[WORD_LEN_MAX], word2[WORD_LEN_MAX]; // buffer para a palavra
    int mode = 0, bsResult1 = -2, bsResult2 = -2;

    for (int i = 0; i < WORD_LEN_MAX; i++)
    {
        word1[i] = '\0';
        word2[i] = '\0';
    }

    // abrir o ficheiro e verificar se foi aberto com sucesso
    palsPointer = (FILE *)fopen(locationPals, "r");
    fileCheck(palsPointer, locationPals);

    statsPointer = (FILE *)fopen(locationStats, "w");
    fileCheck(statsPointer, locationStats);

    // scan dos problemas e escrita da resposta em . pals.stats
    while (fscanf(palsPointer, "%s %s %d", word1, word2, &mode) == 3)
    {
        if (strlen(word1) != strlen(word2) || strlen(word1) > (lenMax) || strlen(word2) > (lenMax))
        {
            fprintf(statsPointer, "%s %s %d \n \n", word1, word2, mode);
            continue;
        }

        bsResult1 = binarySearch(tabs[strlen(word1)], word1, lenCount[strlen(word1)]);
        bsResult2 = binarySearch(tabs[strlen(word2)], word2, lenCount[strlen(word2)]);

        if (bsResult1 == -1 || bsResult2 == -1)
        {
            fprintf(statsPointer, "%s %s %d \n \n", word1, word2, mode);
            continue;
        }

        switch (mode)
        {
        case 1:
            fprintf(statsPointer, "%s %d\n\n", word1, lenCount[strlen(word1)]);
            break;
        case 2:
            fprintf(statsPointer, "%s %d \n%s %d \n\n", word1, bsResult1, word2, bsResult2);
            break;
        default:
            fprintf(statsPointer, "%s %s %d\n\n", word1, word2, mode);
            break;
        }
    }
    fclose(statsPointer);
    fclose(palsPointer);
}

int binarySearch(char **tabs, char *nome, int n)
{
    int lower = 0;
    int upper = n - 1;
    int mid = lower + (upper - lower) / 2;
    int res = 1;
    while (lower <= upper)
    {
        mid = lower + (upper - lower) / 2;
        if (strcmp(nome, (tabs[mid])) == 0)
            res = 0;
        if (res == 0)
            return mid;
        if (strcmp(nome, (tabs[mid])) > 0)
            lower = mid + 1;
        else
            upper = mid - 1;
    }
    return -1;
}

void graphsAdjs(graph **graphs, char ***tabs, int *lenCount, int maxLen)
{
    int i = 0, j = 0, k = 0, wtAux = 0, maxModeAux = 0;

    for (k = 0; k < maxLen; k++)
    {
        if (graphs[k] != NULL && lenCount[k] > 0)
        {
            graphs[k]->adj = (Edge **)calloc(lenCount[k], sizeof(Edge *));
            memoryCheck(graphs[k]->adj);

            for (i = 0; i < lenCount[k]; i++)
            {
                for (j = i; j < lenCount[k]; j++)
                {
                    wtAux = edgeWeight(tabs[k][i], tabs[k][j], k);
                    maxModeAux = graphs[k]->maxMode * graphs[k]->maxMode;
                    if (wtAux > maxModeAux)
                    {
                        continue;
                    }
                    if (wtAux > 0)
                    {
                        graphs[k]->adj[i] = addEdge(graphs[k], i, j, wtAux);
                        graphs[k]->adj[j] = addEdge(graphs[k], j, i, wtAux);
                    }
                    wtAux = 0;
                }
                maxModeAux = 0;
            }
            printf("Grafo %d\n", k);
            printAdj(graphs[k]->adj, lenCount[k]);
            printf("\n");
        }
    }
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
