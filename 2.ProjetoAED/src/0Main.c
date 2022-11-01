#include "0Main.h"

int main(int argc, char* argv[])
{
char *dictLocation=NULL, *palsLocation=NULL, *pathsLocation=NULL;
int *dictLenCount=NULL, *palsOrder=NULL, maxLen=0, nPals=0; 
char ***dicTabs=NULL;
graph **graphsVector=NULL;
Problem **palsTabs=NULL;

int i=0, sn = 0, end = 0;

argsCheck(argc);
dictAndPalsCheck(argv);

dictAndPalsAloc(argv, &dictLocation, &palsLocation);

savePals(palsLocation, &nPals, &palsOrder, &palsTabs, &maxLen);
fillGraphs(palsTabs, maxLen, &graphsVector);

//tratamento do dicionario (guardar e organizar)
saveDict(dictLocation, &dictLenCount, &dicTabs, maxLen, graphsVector);
sortDict(dictLenCount, dicTabs, maxLen, graphsVector);


for (i = 0; i < maxLen; i++)
{
    if (graphsVector[i] != NULL && dictLenCount[i] > 0)
    {
        makeAdjs(graphsVector[i], dicTabs[i], dictLenCount[i], maxLen);

        while(palsTabs[i] != NULL)
        {
        sn = binarySearch(dicTabs[i], palsTabs[i]->word1, dictLenCount[i]);
        end = binarySearch(dicTabs[i], palsTabs[i]->word2, dictLenCount[i]);
        dijkstra(palsTabs[i], sn, dictLenCount[i], end, graphsVector[i]->adj);

        palsTabs[i] = palsTabs[i]->next;
        }
        
        freeGraph(graphsVector[i], maxLen, dictLenCount[i]);
    }
}


//fazer ficheiro de saida
//makePaths(pathsLocation, dictLenCount, dicTabs, palsLocation, maxLen);

freePals(palsTabs, maxLen);
freeDict(dicTabs, dictLenCount, maxLen);
freeOtherMemory(maxLen, graphsVector, palsOrder, dictLenCount, dictLocation, palsLocation, pathsLocation);

return 0;
}
