#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // char fileDict[] = "ficheirosTeste/dicionarios/portugues04-04-sl.dict";
    // char fileDict[] = "ficheirosTeste/dicionarios/testarContagem.dict";
    char locationDict[] = "ficheirosTeste/dicionarios/portugues04-08.dict";
    // char fileDict[] = "ficheirosTeste/dicionarios/portugues04-04-sl.dict";

    FILE *dictPointer;

    // abrir o ficheiro e verificar se foi aberto com sucesso
    dictPointer = (FILE *)fopen(locationDict, "r");
    if (dictPointer == (FILE *)NULL)
    {
        fprintf(stderr, "File %s cannot be read.  Please correct.\n", locationDict);
        exit(0);
    }

    char word[100]; // buffer para a palavra
    int i = 0;

    //fazer scan do dicionario
    while (fscanf(dictPointer, " %s ", word) == 1)
    {
        printf("%s\n", word);
        i++;
    }
    printf("Existem %d palavras no ficheiro.\n", i);


    return 0;
}