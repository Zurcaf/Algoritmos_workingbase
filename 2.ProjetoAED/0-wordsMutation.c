#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headers/0-wordsMutation.h"
#include "headers/1-dicionario.h"
#include "headers/2-pals.h"

#define DICT_EXT ".dict"
#define PALS_EXT ".pals"

int main(int argc, char* argv[])
{
argsCheck(argc);

//mudar para wrdmttns no make file

// char locationDict[] = "ficheirosTeste/dicionarios/portugues04-04-sl.dict";
//char locationDict[] = "ficheirosTeste/dicionarios/testarContagem.dict";
// char locationDict[] = "ficheirosTeste/dicionarios/portugues04-08.dict";
// char locationDict[] = "ficheirosTeste/dicionarios/portugues04-04-sl.dict";
//char* dictLocation = "ficheirosTeste/dicionarios/testarContagem.dict";
char* dictLocation = "ficheirosTeste/dicionarios/portugues04-08.dict";
char* palsLocation = "ficheirosTeste/dicionarios/Simple01.pals";
bool* palsActivation = NULL;

dictAndPalsCheck(argv, dictLocation, palsLocation);
savePals(palsLocation, palsActivation);
saveDictionary(dictLocation, palsActivation);



return 0;
}

void argsCheck(int argc)
{
    if (argc != 3)
    {
        fprintf(stderr, "ERROR: wrong number of arguments!\n");
        exit(1);
    }
}

void dictAndPalsCheck(char *argv[], char *dictLocation, char *palsLocation)
{
    int lenArgs[2], auxLen[2], i=0, j=0;
    char dict[] = DICT_EXT, pals[] = PALS_EXT;

    lenArgs[0] = strlen(argv[1]);
    lenArgs[1] = strlen(argv[2]);
    
    auxLen[0] = lenArgs[0] - (strlen (DICT_EXT));
    auxLen[1] = lenArgs[1] - (strlen (PALS_EXT));

    for(i=0; i<2; i++)
    {
        for(j=auxLen[i]; j<lenArgs[i]; j++)
        {
            if(i==0)
            {
                if(argv[1][j] != dict[j-auxLen[i]])
                {
                    fprintf(stderr, "ERROR: wrong dictionary extension!\n");
                    exit(2);
                }
            }
            else
            {
                if(argv[2][j] != pals[j-auxLen[i]])
                {
                    fprintf(stderr, "ERROR: wrong pals extension!\n");
                    exit(3);
                }
            }
        }
    }
}