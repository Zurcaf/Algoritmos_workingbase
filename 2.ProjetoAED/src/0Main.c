#include "0Main.h"

int main(int argc, char* argv[])
{
char *dictLocation=NULL, *palsLocation=NULL, *pathsLocation=NULL;
int *dictLenCount=NULL, *palsOrder=NULL, maxLen=0, nPals=0; 
char ***dicTabs=NULL;
graph **graphsVector=NULL;
Problem **palsTabs=NULL;

// int i=0;

argsCheck(argc);
dictAndPalsCheck(argv);

dictAndPalsAloc(argv, &dictLocation, &palsLocation);

savePals(palsLocation, &nPals, &palsOrder, &palsTabs, &maxLen);
fillGraphs(palsTabs, maxLen, &graphsVector);

//tratamento do dicionario (guardar e organizar)

saveDict(dictLocation, &dictLenCount, &dicTabs, maxLen, graphsVector);
sortDict(dictLenCount, dicTabs, maxLen, graphsVector);

// alocPaths(&pathsLocation, palsLocation);

// for (i = 0; i < maxLen; i++)
// {
//     if (palsLenCount[i] > 0)
//     {
//         makeGraph(&graphsVector[i],dictLenCount[i], maxLen);
//         dijkstra(graphsVector[i], dictLenCount[i], palsTabs[i], pathsLocation);
//         freeGraph(&graphsVector[i], dictLenCount[i]);
//     }
// }



//makePaths(pathsLocation, dictLenCount, dicTabs, palsLocation, maxLen);

freePals(palsTabs, maxLen);
freeDict(dicTabs, dictLenCount, maxLen);
freeGraph(graphsVector, maxLen, dictLenCount);
freeOtherMemory(palsOrder, dictLenCount,   dictLocation, palsLocation, pathsLocation);

return 0;
}
