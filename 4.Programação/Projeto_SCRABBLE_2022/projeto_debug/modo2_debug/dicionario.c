#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <getopt.h>

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

    file_dicionario = fopen(nome_dicionario, "r");
    if (file_dicionario == NULL)
    {
        printf("não abriu dicionario");
    }

    while (!feof(file_dicionario))
    {
        if (fgets(linha_dicionario, 100, file_dicionario))
        {
            corte_linha_dicionario(linha_dicionario);

            comprimento = strlen(linha_dicionario);
            if (validar_palavra(linha_dicionario, lado_tab, comprimento))
            {
            soma += 1;
            }

        }
    }
    fclose(file_dicionario);
    
    //alocação do pointer do tipo pointer para guardar os endereços das strings
    printf("%d\n", soma);
    char **linha_dic = (char**)calloc((soma + 1),sizeof(char*));
    if (linha_dic == NULL) printf("ERRO a alocar memeoria para as os endereços das linhas!!");

   
int j = 0;
for (int i = lado_tab; i >= 2; i--)
{
     file_dicionario = fopen(nome_dicionario, "r");
    if (file_dicionario == NULL)
    {
        printf("não abriu dicionario");
    }

    while (!feof(file_dicionario))
    {
        if (fgets(linha_dicionario, 100, file_dicionario))
        {
            corte_linha_dicionario(linha_dicionario);
            comprimento = strlen(linha_dicionario);
            if (validar_palavra(linha_dicionario, lado_tab, comprimento))
            {
                if (comprimento == i)
                {
                    char *string = (char*)calloc(comprimento, sizeof (char));
                    if(string == NULL) printf (" Impossivel alocar string");
                    strcpy(string, linha_dicionario);
                    linha_dic[j] = string;
                    j++;
                }
            }
        }
    }
    fclose(file_dicionario);
}
    printf ("%s\n", linha_dic[0]);
    for (int k =0; k<=soma; k++)
    {
        free(linha_dic[k]);
    }
    free(linha_dic);

return 0;
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
