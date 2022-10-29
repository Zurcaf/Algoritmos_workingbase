#include "0Main.h"


void memoryFree(graph **gs, int *lenCount, char ***tabs, int maxLen,  char *statsLocation, char *dictLocation, char *palsLocation)
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
    free(lenCount);
    free(tabs);

    free(statsLocation);
    free(dictLocation);
    free(palsLocation);

    for(i=0; i<maxLen; i++)
    {
        if(gs[i] != NULL)
        {
            free(gs[i]);
        }
    }
    free(gs);
}


void fillGraphs(char *palsLocation,  int *maxLen, graph ***gs)
{
    FILE *fp=NULL;
    char word1[WORD_LEN_MAX] = {0}, word2[WORD_LEN_MAX] = {0};
    int  mode=0;

    fp = fopen(palsLocation, "r");
    fileCheck(fp, palsLocation);

    while (fscanf(fp, "%s %s %d", word1, word2, &mode) == 3)
    {
        if(strlen(word1) > (*maxLen))
        {
            (*maxLen) = strlen(word1);
        }

    }
    if ((*maxLen) == 0)
    {
        fprintf(stderr, "ERROR: no words in file!(.pals)\n");
        exit(6);
    }

    (*maxLen)++;

    *gs = (graph **)calloc((*maxLen), sizeof(graph *));
    memoryCheck(*gs);

    rewind(fp);

    while (fscanf(fp, "%s %s %d", word1, word2, &mode) == 3)
    {
        if((*gs)[strlen(word1)] == NULL)
        {
            initGraph(&(*gs)[strlen(word1)]);
        }
        if((*gs)[strlen(word1)]->maxMode < mode)
        {
            (*gs)[strlen(word1)]->maxMode = mode;
        }
    }
 
    
    fclose(fp);
}

void initGraph(graph **g)
{
    (*g) = (graph *)malloc(sizeof(graph));
    memoryCheck(*g);

    (*g)->vertices = 0;
    (*g)->maxMode = 0;
    (*g)->adj = NULL;
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
