#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headers/0-wordsMutation.h"
#include "headers/1-dicionario.h"
#include "headers/2-pals.h"
#include "headers/3-fileStats.h"



int main(int argc, char* argv[])
{
argsCheck(argc);

//mudar para wrdmttns no make file

// char locationDict[] = "ficheirosTeste/dicionarios/portugues04-04-sl.dict";
//char locationDict[] = "ficheirosTeste/dicionarios/testarContagem.dict";
//char locationDict[] = "ficheirosTeste/dicionarios/portugues04-08.dict";
//char locationDict = "ficheirosTeste/dicionarios/portugues04-04-sl.dict";
//char* dictLocation = "ficheirosTeste/dicionarios/testarContagem.dict";
char* dictLocation;
char* palsLocation;
bool* palsActivation=NULL;

dictAndPalsCheck(argv);
dictAndPalsAloc(argv, &dictLocation, &palsLocation);

//savePals(palsLocation, palsActivation);
fillPalsActivation(palsLocation, &palsActivation);
saveDictionary(dictLocation, palsActivation);

free(palsActivation);
free(dictLocation);
free(palsLocation);

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

void dictAndPalsCheck(char *argv[])
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

void dictAndPalsAloc(char *argv[], char **dictLocation, char **palsLocation)
{
    *dictLocation = (char *)malloc((strlen(argv[1]) + 1) * sizeof(char));
    if (*dictLocation == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }
    strcpy(*dictLocation, argv[1]);

    *palsLocation = (char *)malloc((strlen(argv[2]) + 1) * sizeof(char));
    if (*palsLocation == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }
    strcpy(*palsLocation, argv[2]);
}

void fillPalsActivation(char *palsLocation, bool **palsActivation)
{
    FILE *fp=NULL;
    char word[40] = {0};
    int i=0, maxLen=0;

    fp = fopen(palsLocation, "r");
    if (fp == NULL)
    {     
        fprintf(stderr, "ERROR: could not open file!(.pals)\n");
        exit(5);
    }

    while (fscanf(fp, "%s", word) == 1)
    {
        if(strlen(word) > maxLen)
        {
            maxLen = strlen(word);
        }
    }
    if (maxLen == 0)
    {
        fprintf(stderr, "ERROR: no words in file!\n");
        exit(6);
    }

    maxLen++;

    *palsActivation = (bool *)malloc(maxLen+1 * sizeof(bool));
    if (*palsActivation == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }

    rewind(fp);

    for(i=0; i<maxLen; i++)
    {
        (*palsActivation)[i] = false;   
    }

    while (fscanf(fp, "%s", word) == 1)
    {
        (*palsActivation)[strlen(word)] = true;
    }

    for(int i=0; i<maxLen; i++)
    {
        printf("%d ", (*palsActivation)[i]);
    }
            printf("\n");

    

    fclose(fp);
}