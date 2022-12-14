#include <stdio.h>
#include <stdlib.h>

void inicializar_tab(int lado, char (*tabu)[15][15]);
void imprimir_tab(int lado, char tabu[15][15]);

int main()
{
    int lado_tab=15;
    char tabuleiro[lado_tab][lado_tab];

    printf("Qual é o tamanho do seu tabuleiro? (7/9/11/13/15): ");
    scanf("%d", &lado_tab);
    inicializar_tab(lado_tab, tabuleiro);
    imprimir_tab(lado_tab, tabuleiro);
    printf("%d", lado_tab);


    return 0;
}
void inicializar_tab(int const lado, char tabu[15][15])
{
    int i, j;

    for(i=0;i<lado;i++)
        {
        for(j=0;j<lado;j++)
            {
            tabu[i,j]=".";
            }
        }
}

void imprimir_tab(int lado, char (tabu)[15][15])
{
    for (int i=0; i<lado;i++)
        for (int j=0; i<lado;i++)
            {printf("%d", tabu[lado][lado]);
            printf("\n");
            }
}

