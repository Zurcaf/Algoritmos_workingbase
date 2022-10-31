#include "0Main.h"

int main(int argc, char* argv[])
{
char *dictLocation=NULL, *palsLocation=NULL, *pathsLocation=NULL;
int *dictLenCount=NULL, *palsOrder=NULL, maxLen=0, nPals=0; 
char ***dicTabs=NULL;
graph **graphsVector=NULL;
Problem **palsTabs=NULL;

int i=0;

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
        // dijkstra(graphsVector[i], dictLenCount[i], palsTabs[i], pathsLocation);
        // alocPaths(&pathsLocation, palsLocation);
        freeGraph(graphsVector[i], maxLen, dictLenCount[i]);
    }
}


//fazer ficheiro de saida
//makePaths(pathsLocation, dictLenCount, dicTabs, palsLocation, maxLen);

freePals(palsTabs, maxLen);
freeDict(dicTabs, dictLenCount, maxLen);
freeOtherMemory(maxLen, graphsVector, palsOrder, dictLenCount,   dictLocation, palsLocation, pathsLocation);

return 0;
}
