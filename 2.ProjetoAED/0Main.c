#include "0Main.h"

int main(int argc, char* argv[])
{
char *dictLocation=NULL, *palsLocation=NULL, *pathsLocation=NULL;
int *dictLenCount=NULL, *palsOrder=NULL, maxLen=0, nPals=0; 
char ***dicTabs=NULL;
graph **graphsVector=NULL;
Problem **beginPals=NULL, **endPals=NULL, *aux1 =NULL;

int i=0, sn = 0, end = 0;

argsCheck(argc);
dictAndPalsCheck(argv);

dictAndPalsAloc(argv, &dictLocation, &palsLocation);

savePals(palsLocation, &nPals, &palsOrder, &endPals, &maxLen, &beginPals);
fillGraphs(beginPals, maxLen, &graphsVector);

//tratamento do dicionario (guardar e organizar)
saveDict(dictLocation, &dictLenCount, &dicTabs, maxLen, graphsVector);
sortDict(dictLenCount, dicTabs, maxLen, graphsVector);

for (i = 0; i < maxLen; i++)
{
    if (graphsVector[i] == NULL || dictLenCount[i] == 0)
    {
        aux1 = endPals[i];
        while (aux1 != NULL)
        {
            aux1->mode = -1;
            aux1 = aux1->next;
        }
        continue;
    }

    

    makeAdjs(graphsVector[i], dicTabs[i], dictLenCount[i], maxLen);
    

    aux1 = endPals[i];
    while (aux1 != NULL)
    {
        sn = binarySearch(dicTabs[i], aux1->word1, dictLenCount[i]);
        end = binarySearch(dicTabs[i], aux1->word2, dictLenCount[i]);

        
        if (sn == -1 || end == -1)
        {
            aux1->mode = -1;
            aux1 = aux1->next;
            continue;
        }
        
        dijkstra(aux1, sn, dictLenCount[i], end, graphsVector[i]->adj);
        // printPath(aux1->path, dicTabs[i]);
        aux1 = aux1->next;
    }
    

    freeGraph(graphsVector[i], maxLen, dictLenCount[i]);
}

//printPals(beginPals, maxLen, nPals, palsOrder);

alocPaths(&pathsLocation, palsLocation);

//fazer ficheiro de saida
makePaths(pathsLocation, dictLenCount, dicTabs, maxLen, beginPals, nPals, palsOrder);


freePals(endPals, maxLen, beginPals);
freeDict(dicTabs, dictLenCount, maxLen);
freeOtherMemory(maxLen, graphsVector, palsOrder, dictLenCount, dictLocation, palsLocation, pathsLocation);

return 0;
}
