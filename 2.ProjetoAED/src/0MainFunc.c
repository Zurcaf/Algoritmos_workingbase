#include "0Main.h"

void freeOtherMemory(int maxLen, graph **gs, int * palsOrder, int *dictLenCount,char *statsLocation, char *dictLocation, char *palsLocation)
{
    free(dictLenCount);
    free(palsOrder);

    for(int i=0; i< maxLen; i++)
    {
        if(gs[i] != NULL)
        {
            free(gs[i]);
        }
    }
    free(gs);


    free(statsLocation);
    free(dictLocation);
    free(palsLocation);
}

void freePals (Problem **endPals, int maxLen, Problem **beginPals)
{
    int i=0;
    Problem *aux=NULL, *aux2=NULL;
    for (i = 0; i < maxLen; i++)
    {
        aux = endPals[i];
        while (aux != NULL)
        {
            aux2 = aux->next;
            free(aux->word1);
            free(aux->word2);
            free(aux);
            aux = aux2;
        }
    }
    free(endPals);
    free(beginPals);
}

void freeDict(char ***tabs, int *lenCount, int maxLen)
{
    int i=0, j=0;
        
    for (i = 0; i < maxLen; i++)
    {
        if (lenCount[i] > 0)
        {
            for (j = 0; j < lenCount[i]; j++)
            {
                free(tabs[i][j]);
            }
            free(tabs[i]);
        }
    }
    free(tabs);
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

void memoryCheck(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }
}

void fileCheck(FILE *filePointer, char *fileName)
{
    if (filePointer == NULL)
    {
        fprintf(stderr, "ERROR: could not open file %s!\n", fileName);
        exit(3);
    }
}

void argsCheck(int argc)
{
    if (argc != 3)
    {
        fprintf(stderr, "ERROR: wrong number of arguments!\n");
        exit(1);
    }
}

void cutPals(char **locationPals)
{
    (*locationPals)[(strlen(*locationPals) - strlen(PALS_EXT))] = '\0';
}

void alocPaths(char **locationStats, char *locationPals)
{
    char *locationAux = NULL;

    locationAux = (char *)malloc((strlen(locationPals) + 1) * sizeof(char));
    memoryCheck(locationAux);
    strcpy (locationAux, locationPals);

    (*locationStats) = (char*)calloc(((strlen(locationPals)-(strlen(PALS_EXT))) + (strlen(PATHS_EXT)) + 1), sizeof(char));
    memoryCheck(*locationStats);

    cutPals(&locationAux);
    strcpy((*locationStats), locationAux);

    strcat((*locationStats), PATHS_EXT);

    free(locationAux);
}
