#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headers/1-dicionario.h"

void saveDictionary(char *locationDict, int** lenCount, char ****tabs, int *maxLen, bool* palsActivation)
{
    FILE *dictPointer;

    // abrir o ficheiro e verificar se foi aberto com sucesso
    dictPointer = (FILE *)fopen(locationDict, "r");
    if (dictPointer == (FILE *)NULL)
    {
        fprintf(stderr, "File %s cannot be read.  Please correct.\n", locationDict);
        exit(0);
    }

    char word[40]; // buffer para a palavra
    int i, j;

    //fazer scan do dicionario
    while (fscanf(dictPointer, "%s", word) == 1)
    {
        if (strlen(word) > (*maxLen))
        {
            (*maxLen) = strlen(word);
        }
    }

    //acerto do tamanho maximo para alocação dos vetores
    (*maxLen)++;

    rewind(dictPointer);

    //criar array de inteiros para guardar as ocorrencias de cada tamanho de palavra
    (*lenCount) = (int*)calloc((*maxLen), sizeof(int));
    if ((*lenCount) == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }
    
    //Alocar tabs *** para cada tananho inicializado
    (*tabs) = (char***)calloc((*maxLen), sizeof(char**));
    if ((*tabs) == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }

    //preencher lenCount com o numero de ocorrencias de cada tamanho de palavra
    while (fscanf(dictPointer, "%s", word) == 1)
    {    
        (*lenCount)[strlen(word)]++;
    }

    rewind(dictPointer);

    for(i = 0; i < (*maxLen); i++)
    {
        if ((*lenCount)[i] > 0)
        {
            //alocar memoria para o array de palavras com o tamanho i
            (*tabs)[i] = (char**)calloc((*lenCount)[i], sizeof(char*));
            if ((*tabs)[i] == NULL)
            {
                fprintf(stderr, "ERROR: not enough memory available!\n");
                exit(4);
            }
            for(j=0; j<(*lenCount)[i]; j++)
            {
                //alocar memoria para cada palavra com o tamanho i
                (*tabs)[i][j] = (char*)calloc(i+1, sizeof(char));
                if ((*tabs)[i][j] == NULL)
                {
                    fprintf(stderr, "ERROR: not enough memory available!\n");
                    exit(4);
                }
            }
        }
    }
    
    int* lenCountAux;

    lenCountAux = (int*)calloc((*maxLen), sizeof(int));
    if ((*lenCount) == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }


    while (fscanf(dictPointer, "%s", word) == 1)
    {    

        strcpy((*tabs)[strlen(word)][lenCountAux[strlen(word)]], word);
        lenCountAux[strlen(word)]++;
    }
    
    fclose(dictPointer);

    //dar free a tudo
    free(lenCountAux);
}


// void openFile()
// {

// }
// void fillLenCount()
// {

// }
// void fill()
// {

// }
