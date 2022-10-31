#include "0Main.h"

void savePals(char *palsLocation, int *nPals, int **palsOrder, Problem ***tabs, int* maxLen)
{
    FILE *palsPointer=NULL;
    int i=0, j=0; // variaveis auxiliares

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
    (*tabs) = (Problem**)calloc(8, sizeof(Problem*));
    memoryCheck(*tabs);

    //Alocar palOrder
    (*palsOrder) = (int*)calloc((*nPals), sizeof(int));
    memoryCheck(*palsOrder);

    // preencher lenCount com o numero de ocorrencias de cada tamanho de palavra
    while (fscanf(palsPointer, "%s %s %d", word1, word2, &mode) == 3)
    {
        if (strlen(word1) != strlen(word2))
        {
            *palsOrder[i] = 0;
            temp = initProblem(strlen(word1), strlen(word2));
            addProblem(temp, 0, word1, word2, mode, *tabs);
            i++;
            continue; 
        }
        temp = initProblem(strlen(word1), strlen(word2));
        addProblem(temp, strlen(word1), word1, word2, mode, *tabs);
        (*palsOrder)[i] = strlen(word1);
        i++;
    }

    printPals(*tabs, *maxLen, *nPals, *palsOrder);

    fclose(palsPointer);
}

void addProblem(Problem* p, int size, char* word1, char* word2, int mode, Problem **tabs)
{
    strcpy(p->word1, word1);
    strcpy(p->word2, word2);
    p->mode = mode;
    
    p->next = (tabs)[size];
    tabs[size] = p; 
}

void printPals(Problem **tabs, int maxLen, int nPals, int* palsOrder)
{
    int i=0;
    Problem* temp, **aux;

    aux = (Problem**)calloc(maxLen, sizeof(Problem*));
    memoryCheck(aux);

    for(i=0; i<nPals; i++)
    {
        
        // temp = tabs[i];
        // if (temp != NULL)
        //     printf("Tamanho %d\n", i);
        
        // while(temp != NULL)
        // {
        //     printf("%s %s %d\n", temp->word1, temp->word2, temp->mode);
        //     temp = temp->next;
        // }
    }
    printf("\n");
    printf("PalsOrder: ");
    for (i=0; i<nPals; i++)
    {
        printf("%d ", palsOrder[i]);
    }
}


Problem* initProblem(int size1, int size2)
{
    Problem *p = (Problem*)malloc(sizeof(Problem));
    memoryCheck(p);
    p->word1 = (char*)malloc((size1 +1) * sizeof(char));
    memoryCheck(p->word1);
    p->word2 = (char*)malloc((size2 +1) * sizeof(char));
    memoryCheck(p->word2);
    p->mode = 0;
    p->orderIndex = 0;
    p->next = NULL;
    return p;
}

void fillGraphs(Problem **palsTabs, int maxLen, graph ***gs)
{
    *gs = (graph **)calloc(maxLen, sizeof(graph *));
    memoryCheck(*gs);

    int i=0;
    for(i=0; i< maxLen; i++)
    {
        if(palsTabs[i] != NULL)
        {
            initGraph(&(*gs)[i]);
        }
    }

}

void initGraph(graph **g)
{
    (*g) = (graph *)malloc(sizeof(graph));
    memoryCheck(*g);

    (*g)->vertices = 0;
    (*g)->maxMode = 0;
    (*g)->adj = NULL;
}