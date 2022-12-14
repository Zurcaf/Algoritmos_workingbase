#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char nome_aloc_estat[100], *nome_aloc_din;
    long limit;

    scanf("%ld", &limit);
    nome_aloc_din=(char*) malloc(limit*sizeof(char));
    printf("o tamanho de um inteiro é: %ld\n", sizeof(int));
    printf("o tamanho de um character é: %ld\n", sizeof(char));
    printf("o tamanho de um float é: %ld\n", sizeof(float));
    printf("o tamanho de um double é: %ld\n", sizeof(double));

    if (nome_aloc_din == NULL)
    {   printf("Erro não foi possivel alocar o bloco de memoria\n");
        strcpy(nome_aloc_din, "vai dar erro!!!");
        printf("%s", nome_aloc_din);
    }
    else
    {   printf("bloco de memória alocado com sucesso\n");
        strcpy(nome_aloc_din, "não deu erro!!!");
        printf("%s", nome_aloc_din);
    }
    free(nome_aloc_din);
    return 0;
}
