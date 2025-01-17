#include "0Main.h"

void saveDict(char *locationDict, int** lenCount, char ****tabs, int maxLen, graph **gs)
{
    FILE *dictPointer=NULL;

    // abrir o ficheiro e verificar se foi aberto com sucesso
    dictPointer = (FILE *)fopen(locationDict, "r");
    fileCheck(dictPointer, locationDict);

    char word[WORD_LEN_MAX]; // buffer para a palavra
    int i=0, j=0; // variaveis auxiliares
    bool flag = false; 

    //criar array de inteiros para guardar as ocorrencias de cada tamanho de palavra
    (*lenCount) = (int*)calloc(maxLen, sizeof(int));
    memoryCheck(*lenCount);
    
    //Alocar tabs *** para cada tananho inicializado
    (*tabs) = (char***)calloc(maxLen, sizeof(char**));
    memoryCheck(*tabs);

    //preencher lenCount com o numero de ocorrencias de cada tamanho de palavra
    while (fscanf(dictPointer, "%s", word) == 1)
    {
        if(strlen(word)< maxLen && gs[strlen(word)] != NULL)
        {
            (*lenCount)[strlen(word)]++;
        }
        flag = true;
    }

    if(flag == false)
    {
        fprintf(stderr, "ERROR: no words in file!(.dict)\n");
        exit(6);
    }
    
    rewind(dictPointer);

    for(i = 0; i < maxLen; i++)
    {
        if ((*lenCount)[i] > 0)
        {
            //alocar memoria para o array de palavras com o tamanho i
            (*tabs)[i] = (char**)calloc((*lenCount)[i], sizeof(char*));
            memoryCheck((*tabs)[i]);

            for(j=0; j<(*lenCount)[i]; j++)
            {
                //alocar memoria para cada palavra com o tamanho i
                (*tabs)[i][j] = (char*)calloc(i+1, sizeof(char));
                memoryCheck((*tabs)[i][j]);
            }
        }
    }
    
    int* lenCountAux = NULL;

    lenCountAux = (int*)calloc(maxLen, sizeof(int));
    memoryCheck(lenCountAux);

    while (fscanf(dictPointer, "%s", word) == 1)
    {    
        if(strlen(word)< maxLen && gs[strlen(word)] != NULL)
        {
            strcpy((*tabs)[strlen(word)][lenCountAux[strlen(word)]], word);
            lenCountAux[strlen(word)]++;
        }
    }
    
    fclose(dictPointer);

    //dar free a tudo
    free(lenCountAux);
}

void sortDict(int *lenCount, char ***tabs, int maxLen, graph **gs)
{
    int i;
    for(i = 0; i < maxLen; i++)
    {
        if (lenCount[i] > 0 && gs[i] != NULL)
        {
            qsort(tabs[i], lenCount[i], sizeof(char*), compare);
        }
    }
    
    // int j;
    // for(i = 0; i < maxLen; i++)
    // {
    //     if (lenCount[i] > 0)
    //     {
    //         for(j = 0; j < lenCount[i]; j++)
    //         {
    //             printf("%s\n", tabs[i][j]);
    //         }
    //     }
    // } 
}

int compare(const void *a, const void *b) 
{ 

// fazer o casting do void pointer para o tipo de variavél dos elementos do vector.
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;

    return strcmp(*str_a, *str_b); // r=0 se forem iguais. r<0 -> 'a' deve estar antes do 'b'. r>0 -> 'a' deve estar depois de 'b'.
} 


// void fillLenCount()
// {

// }
// void fill()
// {

// }
