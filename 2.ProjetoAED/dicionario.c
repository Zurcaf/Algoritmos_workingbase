#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // char locationDict[] = "ficheirosTeste/dicionarios/portugues04-04-sl.dict";
    char locationDict[] = "ficheirosTeste/dicionarios/testarContagem.dict";
    // char locationDict[] = "ficheirosTeste/dicionarios/portugues04-08.dict";
    // char locationDict[] = "ficheirosTeste/dicionarios/portugues04-04-sl.dict";

    FILE *dictPointer;

    // abrir o ficheiro e verificar se foi aberto com sucesso
    dictPointer = (FILE *)fopen(locationDict, "r");
    if (dictPointer == (FILE *)NULL)
    {
        fprintf(stderr, "File %s cannot be read.  Please correct.\n", locationDict);
        exit(0);
    }

    char word[100]; // buffer para a palavra
    int maxLen = 0;
    int i;

    //fazer scan do dicionario
    while (fscanf(dictPointer, " %s ", word) == 1)
    {
        if (strlen(word) > maxLen)
        {
            maxLen = strlen(word);
        }
    }

    //acerto do tamanho maximo para alocação dos vetores
    maxLen++;

    rewind(dictPointer);

    //criar array de inteiros para guardar as ocorrencias de cada tamanho de palavra
    int* lenCount;
    lenCount = (int*)calloc(maxLen, sizeof(int));
    if (lenCount == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }
    
    //criar ponteiro para array de strings para guardar diferentes tamanhos de palavras
    char*** tabs;
    tabs = (char***)calloc(maxLen, sizeof(char**));
    if (tabs == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }

    //preencher lenCount com o numero de ocorrencias de cada tamanho de palavra
    while (fscanf(dictPointer, " %s ", word) == 1)
    {    
        lenCount[strlen(word)]++;
    }

    rewind(dictPointer);

    for(i = 0; i < maxLen; i++)
    {
        if (lenCount[i] > 0)
        {
            //alocar memoria para o array de strings
            tabs[i] = (char**)calloc(lenCount[i], sizeof(char*));
            if (tabs[i] == NULL)
            {
                fprintf(stderr, "ERROR: not enough memory available!\n");
                exit(4);
            }
            //alocar espaço para cada palavra
            tabs[i][lenCount[i]] = (char*)calloc(i, sizeof(char));
            if (tabs[i][lenCount[i]] == NULL)
            {
                fprintf(stderr, "ERROR: not enough memory available!\n");
                exit(4);
            }
        }
    }

    //claramente repensar nisto o espaço esta alocado mas devia
    //fazer isto numa função porque vou alterar o valor do lenCount e não quero pois da jeito
    //para saber quantas palavras de cada tamanho tenho
    //proxima coisa a fazer dividir isto em funções e criar a struct cominformação do file

    // while (fscanf(dictPointer, " %s ", word) == 1)
    // {    
    //     tabs[strlen(word)][lenCount[strlen(word)]-1] = word;
    //     lenCount[strlen(word)] -= 1;        
    // }

    return 0;
}