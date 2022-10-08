#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void corte_linha_dicionario (char linha[]);

bool validar_palavra (char[], int, int);

int main()
{
    char nome_dicionario[50] = "pt_PT.dic";
    int lado_tab = 15;
    int comprimento;

    int soma =0;

    FILE *file_dicionario;
    char linha_dicionario[100];
    // int soma[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    

    //
    char dicionario[32000][15];

    file_dicionario = fopen(nome_dicionario, "r");
    if (file_dicionario == NULL)
    {
        printf("não abriu dicionario");
    }
    int line=0;
    while (!feof(file_dicionario))
    {
        if (fgets(linha_dicionario, 100, file_dicionario))
        {
            corte_linha_dicionario(linha_dicionario);

            comprimento = strlen(linha_dicionario);
            if (validar_palavra(linha_dicionario, lado_tab, comprimento))
            {
            // if (strlen(linha_dicionario) == 2)
            // for (int j=0; j<100;j++ )
            // dicionario[line][j]= linha_dicionario[j];
            strcpy(dicionario[line], linha_dicionario);
            printf("%s\n",dicionario[line]);
            line++;
            soma++;
            // printf("%s\n", linha_dicionario);
            // soma += 1;
            }

        }
    }
    fclose(file_dicionario);
    printf ("%d\n", soma);

  
    // char **ptr_strings;
    // for (int i = 2; i <= lado_tab; i++)
    // {
    //     char **ptr_strings = (char **)malloc(sizeof(char *) * soma);
    // }
    // int i = 0;
    // while (!feof(file_dicionario))
    // {
    //     if (fgets(linha_dicionario, 100, file_dicionario))
    //     {
    //         corte_linha_dicionario(linha_dicionario);

    //         comprimento = strlen(linha_dicionario);
    //         if (validar_palavra(linha_dicionario, lado_tab, comprimento))
    //         {
    //             ptr_strings[i++] = (char *)malloc(sizeof(char) * (comprimento + 1));
    //         }
    //     }
    // }
    // fclose(file_dicionario);
    // for (int i = 0; i <= lado_tab; i++)
    // {
    //     free(ptr_strings[i++]);
    // }
}

bool validar_palavra(char palavra[], int lado_tab, int comprimento)
{
    bool flag = true;

    for (int i = 0; i < comprimento; i++)
    {
        int valor_letra = (int)palavra[i];
        if ((valor_letra < 97 || valor_letra > 122))
        {
            flag = false;
        }
    }

    if (comprimento < 2 || comprimento > lado_tab)
        {
        flag = false;
        }

    return flag;
}

void corte_linha_dicionario (char linha[])
{
    for (int i = 0; i< strlen(linha); i++)
    {
        if (linha[i] == '\t') linha[i] = '\0';
        if (linha[i] == '/' ) linha[i] = '\0';
        if (linha[i] == ' ') linha[i] = '\0';
        if (linha[i] == '\n') linha[i] = '\0';
    }
}
