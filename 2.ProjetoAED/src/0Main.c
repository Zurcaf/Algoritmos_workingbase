#include "0Main.h"

int main(int argc, char* argv[])
{
char *dictLocation=NULL, *palsLocation=NULL, *pathsLocation=NULL;
int *lenCount=NULL, maxLen=0; 
char*** tabs=NULL;
graph **graphs=NULL;


argsCheck(argc);
dictAndPalsCheck(argv);

dictAndPalsAloc(argv, &dictLocation, &palsLocation);

fillGraphs(palsLocation, &maxLen, &graphs);

//tratamento do dicionario (guardar e organizar)
saveDict(dictLocation, &lenCount, &tabs, maxLen, graphs);
sortDict(lenCount, tabs, maxLen, graphs);


alocPaths(&pathsLocation, palsLocation);   
makePaths(pathsLocation, lenCount, tabs, palsLocation, maxLen);

memoryFree(graphs, lenCount, tabs, maxLen, dictLocation, palsLocation, pathsLocation);

return 0;
}
