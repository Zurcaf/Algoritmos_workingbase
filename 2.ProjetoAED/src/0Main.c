#include "0Main.h"

int main(int argc, char* argv[])
{
char *dictLocation=NULL, *palsLocation=NULL, *statsLocation=NULL;
bool *reqPals=NULL;
int *lenCount=NULL, maxLen=0;
char*** tabs=NULL;

//verificações dos argumentos (quantidade e extensões)
argsCheck(argc);
dictAndPalsCheck(argv);

//alocação de memoria para cada um dos nomes do ficheiro
dictAndPalsAloc(argv, &dictLocation, &palsLocation);

//abertura do ficheiro pals verificar que comprimentos de palavras retirar do dicionario
fillReqPals(palsLocation, &reqPals, &maxLen);

//tratamento do dicionario (guardar e organizar)
saveDict(dictLocation, &lenCount, &tabs, maxLen, reqPals);
sortDict(lenCount, tabs, maxLen, reqPals);

//leitura do pals e fazer stats
getStats(&statsLocation, lenCount, tabs, palsLocation, maxLen);

//libertação de toda a memoria alocada
memoryFree(lenCount, tabs, maxLen, reqPals, dictLocation, palsLocation, statsLocation);

return 0;
}