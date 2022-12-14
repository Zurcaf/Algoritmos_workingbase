#include "0Main.h"

void savePals(char *palsLocation, int *nPals, int **palsOrder, Problem ***tabs, int* maxLen, Problem ***beginPals)
{
    FILE *palsPointer=NULL;
    int i=0, wtAux=0; // variaveis auxiliares

    char word1[WORD_LEN_MAX] = {0}, word2[WORD_LEN_MAX] = {0};
    int  mode=0;
    Problem* temp;

     // abrir o ficheiro e verificar se foi aberto com sucesso
    palsPointer = (FILE *)fopen(palsLocation, "r");
    fileCheck(palsPointer, palsLocation);

    while (fscanf(palsPointer, "%s %s %d", word1, word2, &mode) == 3)
    {
        if(strlen(word1) > (*maxLen))
        {
            (*maxLen) = strlen(word1);
        }
        (*nPals)++;
    }
    
    (*maxLen)++;

    if ((*nPals) == 0)
    {
        fprintf(stderr, "ERROR: no words in file!(.pals)\n");
        exit(6);
    }

    rewind(palsPointer);
    
    //Alocar tabs *** para cada tananho inicializado
    (*tabs) = (Problem**)calloc(*maxLen, sizeof(Problem*));
    memoryCheck(*tabs);

    (*beginPals) = (Problem**)calloc(*maxLen, sizeof(Problem*));
    memoryCheck(*beginPals);


    //Alocar palOrder
    (*palsOrder) = (int*)calloc((*nPals), sizeof(int));
    memoryCheck(*palsOrder);

    // preencher lenCount com o numero de ocorrencias de cada tamanho de palavra
    while (fscanf(palsPointer, "%s %s %d", word1, word2, &mode) == 3)
    {
        temp = initProblem(strlen(word1), strlen(word2));

        if (strlen(word1) != strlen(word2) || mode <= 0)
        {
            (*palsOrder)[i] = 0;
            if ((*tabs)[0] == NULL)
            {
                (*beginPals)[0] = temp;
            }
            
            addProblem(temp, 0, word1, word2, mode, tabs);
            temp->mode = -1;
            temp->indexOrder = i;
            i++;
            continue; 
        }

        if((*tabs)[strlen(word1)] == NULL)
        {
            (*beginPals)[strlen(word1)] = temp;
        }
        
        wtAux = charDiff(word1, word2, strlen(word1), mode);

        if ((wtAux == 0))
            mode = 0;

        if (mode > wtAux)
            mode = wtAux;

        addProblem(temp, strlen(word1), word1, word2, mode, tabs);
        (*palsOrder)[i] = strlen(word1);
        temp->indexOrder = i;
        i++;
    }

    //printPals(*beginPals, *maxLen, *nPals, *palsOrder);

    fclose(palsPointer);
}

int charDiff(char *word1, char *word2, int k, int maxDiff)
{
    int i = 0, count = 0;

    for (i = 0; i < k; i++)
    {
        if (word1[i] != word2[i])
        {
            count++;
        }
    }

    return count;
}

void addProblem(Problem* p, int size, char* word1, char* word2, int mode, Problem ***tabs)
{
    strcpy(p->word1, word1);
    strcpy(p->word2, word2);
    p->mode = mode;
    if((*tabs)[size] != NULL)
        (*tabs)[size]->previous = p;

    p->next = (*tabs)[size];
    (*tabs)[size] = p; 
}

void printPals(Problem **tabs, int maxLen, int nPals, int* palsOrder)
{
    int i=0;
    Problem* temp, **aux;

    aux = (Problem**)calloc(maxLen, sizeof(Problem*));
    memoryCheck(aux);

    for (i = 0; i < maxLen; i++)
    {
        aux[i] = tabs[i];
    }

    for(i=0; i<nPals; i++)
    {
        if(aux[palsOrder[i]] != NULL)
        {
        temp = aux[palsOrder[i]];
        printf("%s %s %d      %d\n", temp->word1, temp->word2, temp->mode, temp->indexOrder);
        aux[palsOrder[i]] = temp->previous;
        }
    }
    printf("PalsOrder: ");
    for (i=0; i<nPals; i++)
        printf("%d ", palsOrder[i]);
    
    printf("\n");

    free(aux);
}


Problem* initProblem(int size1, int size2)
{
    Problem *p = (Problem*)calloc(1, sizeof(Problem));
    memoryCheck(p);
    p->word1 = (char*)malloc((size1 +1) * sizeof(char));
    memoryCheck(p->word1);
    p->word2 = (char*)malloc((size2 +1) * sizeof(char));
    memoryCheck(p->word2);
    p->mode = 0;
    p->next = NULL;
    p->previous = NULL;
    p->indexOrder = 0;
    p->path = NULL;

    return p;
}


