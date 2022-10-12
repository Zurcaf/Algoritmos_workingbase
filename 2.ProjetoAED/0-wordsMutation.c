#include "headers/0-wordsMutation.h"

//mudar para wrdmttns no make file

int main(int argc, char* argv[])
{
char *dictLocation=NULL, *palsLocation=NULL, *statsLocation=NULL;
//char *locationDict="ficheirosTeste/dicionarios/portugues04-04-sl.dict";
//char *locationDict="ficheirosTeste/dicionarios/testarContagem.dict";
//char *locationDict="ficheirosTeste/dicionarios/portugues04-08.dict";
bool *reqPals=NULL;
int *lenCount=NULL, i=0, j=0, maxLen=0;
char*** tabs=NULL;


argsCheck(argc);
dictAndPalsCheck(argv);
dictAndPalsAloc(argv, &dictLocation, &palsLocation);
fillReqPals(palsLocation, &reqPals, &maxLen);
saveDict(dictLocation, &lenCount, &tabs, maxLen, reqPals);
sortDict(lenCount, tabs, maxLen, reqPals);
getStats(&statsLocation, lenCount, tabs, palsLocation);


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

free(reqPals);
free(statsLocation);
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

void fillReqPals(char *palsLocation, bool **palsActivation, int *maxLen)
{
    FILE *fp=NULL;
    char word1[WORD_LEN_MAX] = {0}, word2[WORD_LEN_MAX] = {0};
    int i=0, mode=0;

    fp = fopen(palsLocation, "r");
    if (fp == NULL)
    {     
        fprintf(stderr, "ERROR: could not open file!(.pals)\n");
        exit(5);
    }

    while (fscanf(fp, "%s %s %d", word1, word2, &mode) == 3)
    {
        if(strlen(word1) > (*maxLen))
        {
            (*maxLen) = strlen(word1);
        }
//        printf("word1: %s word2: %s mode: %d maxLen: %d\n", word1, word2, mode, (*maxLen));
    }
    if ((*maxLen) == 0)
    {
        fprintf(stderr, "ERROR: no words in file!(maxlen)\n");
        exit(6);
    }

    (*maxLen)++;

    *palsActivation = (bool *)malloc((*maxLen)+1 * sizeof(bool));
    if (*palsActivation == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }

    rewind(fp);

    for(i=0; i<(*maxLen); i++)
    {
        (*palsActivation)[i] = false;   
    }

    while (fscanf(fp, "%s %s %d", word1, word2, &mode) == 3)
    {
        (*palsActivation)[strlen(word1)] = true;
    }

    // for(int i=0; i<(*maxLen); i++)
    // {
    //     printf("%d ", (*palsActivation)[i]);
    // }
    //         printf("\n");

    fclose(fp);
}