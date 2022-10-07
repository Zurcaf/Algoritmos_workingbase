#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <getopt.h>

#define LADO_MAX_TAB 15

typedef struct cords
{
    char coordenadas[20];
    int coluna;
    int linha;
    char direcao;
} cords;

typedef struct Info2
{
    cords cords;
    char palavra[50];
    int comprimento;
    int pontos;
} Info2;

//inicializa o tabuleiro vazio
void init_tabuleiro_vazio(char matriz_tab[][LADO_MAX_TAB], int lado_tab);

//coloca o tabuleiro do ficheiro no computador
void init_tabuleiro_file(char nome_ficheiro[], char matriz_tab[][LADO_MAX_TAB], int lado_tab);

//confirmar se o tabuleiro está no formato correto
bool validar_tabuleiro (char matriz_tab[][LADO_MAX_TAB], int lado_tab);

//retira excesso das palavras
void corte_linha_dicionario (char linha[]);

//verifica se estão dentro do alfabeto do jogo
bool validar_palavra_dicionario (char[], int, int);

//aloca o dicionario
char** init_dicionario (char nome_dicionario[], int lado_tab, int *n_linhas);

void free_dicionario (char **linhas_dic, int n_palavras);

//imprimir o tabuleiro
void print_tabuleiro(char matriz_tab[][LADO_MAX_TAB], int lado_tab);

// verificar verifica a ocupação de um local na matriz
bool ocupacao_local_matriz(char centro);

Info2 procurar_jogada_primeira (char matriz_tab[][LADO_MAX_TAB], Info2 hipotese, Info2 jogada, int lado_tab, char local_palavra[], char** linha_dic, int linhas_dicionario, cords casa);

Info2 procurar_jogada_restantes (char matriz_tab[][LADO_MAX_TAB], Info2 hipotese, Info2 jogada, int lado_tab, char local_palavra[], char** linha_dic, int linhas_dicionario, cords casa);

void calcular_casas (char matriz_tab[][LADO_MAX_TAB], int lado_tab, cords casas[]);

bool numero_digitos_linha (char jogada[]);

void init_local_palavra_algoritmo(char matriz_tab[][LADO_MAX_TAB], char coluna, int linha, char direcao, int comprimento, char lado_palavra[]);

bool validar_palavra_primeira (char linha_palavra[], char palavra[], int lado_tab, int comprimento_palavra, char local_palavra[]);

bool validar_palavra (char linha_palavra[], Info2 hipotese, int lado_tab, char local_palavra[]);

int valor_letra (char letra);

int calcular_pontos_jogada (char local_palavra[], char palavra[], int comprimento_palavra);

void print_palavra (char matriz_tab[][LADO_MAX_TAB], char palavra[], int coluna, int linha, char direcao, int lado_tab);


int main()
{
    int lado_tab = 9;
    bool tab_file = false;
    char ficheiro_tabuleiro_inicio[] = "jkenwejk";
    char nome_dicionario[50] = "dicionarios/words";

    bool impossivel = false;

    char **linha_dic;
    int numero_linhas_dicionario;
    char matriz_tab[LADO_MAX_TAB][LADO_MAX_TAB];
    char local_palavra[LADO_MAX_TAB] = {'\0'};

    int pontos_totais = 0;
    int numero_jogada = 0;

    cords casa = {};
    cords casas [250] = {};
    Info2 jogada = {};
    Info2 hipotese = {};

    if (tab_file)
    {
        init_tabuleiro_file(ficheiro_tabuleiro_inicio, matriz_tab, lado_tab);
        if (validar_tabuleiro(matriz_tab, lado_tab))
            return 0;
    }
    else
    init_tabuleiro_vazio(matriz_tab, lado_tab);
    
    linha_dic = init_dicionario(nome_dicionario, lado_tab, &numero_linhas_dicionario);
    do
    {
        if (ocupacao_local_matriz(matriz_tab[lado_tab / 2][lado_tab / 2]))
        {
            // cordenadas para ocupar são 
            casa.coluna = 4;
            casa.linha = 4;
            casa.direcao = 'H';
            jogada = procurar_jogada_primeira(matriz_tab, hipotese, jogada, lado_tab, local_palavra, linha_dic, numero_linhas_dicionario, casa);
        }
        else
        {
        for (int k = 0; k <250; k++)
        {
        casas[k].coluna = 0;
        casas[k].linha = 0;
        casas[k].direcao = 'H';
        }
        calcular_casas (matriz_tab,lado_tab,casas);
         for (int k = 0; k <250; k++)
        {
        casas[k].direcao = 'H';
        }
        for (int k=0; k<250; k++)
        {
            hipotese = procurar_jogada_restantes(matriz_tab, hipotese, jogada, lado_tab, local_palavra, linha_dic, numero_linhas_dicionario, casas[k]);
            if (hipotese.pontos > jogada.pontos)
            {
                jogada = hipotese;
            }
        }
         for (int k = 0; k <250; k++)
        {
        casas[k].direcao = 'V';
        }
         for (int k=0; k<250; k++)
        {
            hipotese = procurar_jogada_restantes(matriz_tab, hipotese, jogada, lado_tab, local_palavra, linha_dic, numero_linhas_dicionario, casas[k]);
            if (hipotese.pontos > jogada.pontos)
            {
                jogada = hipotese;
            }
        }
        }

        pontos_totais += jogada.pontos;
        print_palavra(matriz_tab, jogada.palavra, jogada.cords.coluna, jogada.cords.linha, jogada.cords.direcao, lado_tab);

        numero_jogada++;
        printf("\nJogada %d: %c%d%c %s Pontos: %d\n", numero_jogada, (((char)jogada.cords.coluna)+49), ((char)jogada.cords.linha +1), jogada.cords.direcao, jogada.palavra, jogada.pontos);
        print_tabuleiro(matriz_tab, lado_tab);
        if (sizeof(casas) == 250) impossivel = true;
    } while (!impossivel);

    free_dicionario(linha_dic, numero_linhas_dicionario);
    printf("Total de pontos: %d\nFim do jogo.\n", pontos_totais);
}

void init_tabuleiro_vazio(char matriz_tab[][LADO_MAX_TAB], int lado_tab)
{
    int i = 0, j = 0;
    for (i = 0; i < lado_tab; i++)
    {
        for (j = 0; j < lado_tab; j++)
        {
            matriz_tab[i][j] = '.';
            if ((i == j) || (i + j == lado_tab - 1))
                matriz_tab[i][j] = '2';
            if (j == 0 || j == lado_tab - 1)
            {
                if ((i == j) || (i + j == lado_tab - 1))
                    matriz_tab[i][j] = '$';
            }
            if (j == lado_tab / 2)
            {
                if (i == 0 || i == lado_tab - 1)
                    matriz_tab[i][j] = '3';
            }
            if (i == lado_tab / 2)
            {
                if (j == 0 || j == lado_tab - 1)
                    matriz_tab[i][j] = '3';
            }
            if (j == (lado_tab / 2) - 1 || j == (lado_tab / 2) + 1)
            {
                if (i == 1 || i == (lado_tab - 2))
                    matriz_tab[i][j] = '#';
            }
            if (i == (lado_tab / 2) - 1 || i == (lado_tab / 2) + 1)
            {
                if (j == 1 || j == (lado_tab - 2))
                    matriz_tab[i][j] = '#';
            }
        }
    }
}

void init_tabuleiro_file(char nome_ficheiro[], char matriz_tab[][LADO_MAX_TAB], int lado_tab)
{
    FILE *file_tab;
    char *linha_separada[lado_tab + 1];
    char linha_ficheiro[100];

    char delim[] = " ";
    int indice_linha = 0;
    int i = 0;

    file_tab = fopen(nome_ficheiro, "r");

    if (file_tab == NULL)
        printf("Problemas na abertura do ficheiro");

    while (!feof(file_tab))
    {
        if (fgets(linha_ficheiro, 100, file_tab))
        {
            i = 0;
            char *ptr_linha = strtok(linha_ficheiro, delim);
            while (ptr_linha != NULL)
            {
                linha_separada[i++] = ptr_linha;
                ptr_linha = strtok(NULL, delim);
            }
            for (i = 1; i <= lado_tab; i++)
            {
                matriz_tab[indice_linha][i - 1] = *linha_separada[i];
            }
            indice_linha++;
        }
    }
}

bool validar_tabuleiro(char matriz_tab[][LADO_MAX_TAB], int lado_tab)
{
    bool flags = false;
    int valor_caract;

    for (int i = 0; i < lado_tab; i++)
    {
        for (int j = 0; j < lado_tab; j++)
        {
            // ver caracteres validos num tabuleiro vazio
            if (matriz_tab[i][j] != '$' && matriz_tab[i][j] != '3' && matriz_tab[i][j] != '2' && matriz_tab[i][j] != '#' && matriz_tab[i][j] != '.')
            {
                valor_caract = (int)matriz_tab[i][j];

                // ver se os que não validos são letras
                if (valor_caract > 90 && valor_caract < 123)
                {
                    // verificar foi jogada a primeira jogada neste tabuleiro com letras
                    if (!ocupacao_local_matriz(matriz_tab[7][7]))
                    {
                        printf("ERRO: Tabuleiro com caracteres invalidos ou com jogos invalidos (sem palavra no centro)\n");
                        flags = true;
                    }
                }
            }
        }
    }

    return flags;
}

char** init_dicionario(char nome_dicionario[], int lado_tab, int *n_linhas)
{
    int comprimento;
    *n_linhas = 0;

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
            if (validar_palavra_dicionario(linha_dicionario, lado_tab, comprimento))
            {
                *n_linhas += 1;
            }
        }
    }
    fclose(file_dicionario);

    // alocação do pointer do tipo pointer para guardar os endereços das strings
    char **linha_dic = (char **)calloc((*n_linhas + 1), sizeof(char *));
    if (linha_dic == NULL)
        printf("ERRO a alocar memeoria para as os endereços das linhas!!");

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
                if (validar_palavra_dicionario(linha_dicionario, lado_tab, comprimento))
                {
                    if (comprimento == i)
                    {
                        char *string = (char *)calloc(comprimento, sizeof(char));
                        if (string == NULL)
                            printf(" Impossivel alocar string");
                        strcpy(string, linha_dicionario);                        
                        linha_dic[j] = string;
                        j++;
                    }
                }
            }
        }
        fclose(file_dicionario);
    }
    return linha_dic;
    
}

void free_dicionario (char ** linha_dic, int n_palavras)
{
    for (int k = 0; k <= n_palavras; k++)
    {
        free(linha_dic[k]);
    }
    free(linha_dic);
}

bool validar_palavra_dicionario(char palavra[], int lado_tab, int comprimento)
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

void print_tabuleiro(char matriz_tab[][LADO_MAX_TAB], int lado_tab)

{
    int linha = 0, coluna = 0;
    char letra = 'A';

    for (linha = 0; linha < lado_tab; linha++)
    {
        if (linha < 9)
            printf(" ");
        printf("%d", (linha + 1));
        for (coluna = 0; coluna < lado_tab; coluna++)
        {
            printf(" %c", matriz_tab[linha][coluna]);
        }
        printf("\n");
    }
    printf("  ");

    coluna = 0;
    for (coluna = 0; coluna < lado_tab; coluna++)
    {
        printf(" %c", letra);
        letra += 1;
    }
    printf("\n");
    printf("\n");
}

bool ocupacao_local_matriz(char centro)
{
    int valor_caract;
    valor_caract = (int)centro;
    if (valor_caract > 96 && valor_caract < 123)
        return false;
    else
        return true;
}

Info2 procurar_jogada_primeira (char matriz_tab[][LADO_MAX_TAB], Info2 hipotese, Info2 jogada, int lado_tab, char local_palavra[], char** linha_dic, int linhas_dicionario, cords casa)
{
    int numero_shifts = 0;
    int i = 0;
    hipotese.cords.linha = 4;
    hipotese.cords.direcao = 'H';
    
    for (hipotese.comprimento = lado_tab; hipotese.comprimento >= 2; hipotese.comprimento--)
    {
        numero_shifts = lado_tab - hipotese.comprimento;
        for (hipotese.cords.coluna = 0; hipotese.cords.coluna <= numero_shifts; hipotese.cords.coluna++)
        {
            init_local_palavra_algoritmo(matriz_tab, hipotese.cords.coluna, hipotese.cords.linha, hipotese.cords.direcao, hipotese.comprimento, local_palavra);
            if (hipotese.cords.coluna <= casa.coluna && (hipotese.cords.coluna + hipotese.comprimento) >= casa.coluna)
            {
                // testestar todas as palavras com o comprimento hipotetico
                for (i = 0 ; i<linhas_dicionario; i ++)
                {
                    if (strlen(linha_dic[i]) == hipotese.comprimento)
                    {
                            hipotese.pontos = calcular_pontos_jogada(local_palavra, linha_dic[i], hipotese.comprimento);
                        if (hipotese.pontos > jogada.pontos)
                        {
                            strcpy(hipotese.palavra, linha_dic[i]);
                            hipotese.pontos = calcular_pontos_jogada(local_palavra, linha_dic[i], hipotese.comprimento);
                            jogada = hipotese;

                        }
                    }
                }
            }
        }
    }
    return jogada;
}

Info2 procurar_jogada_restantes (char matriz_tab[][LADO_MAX_TAB], Info2 hipotese, Info2 jogada, int lado_tab, char local_palavra[], char** linha_dic, int linhas_dicionario, cords casas)
{
    int numero_shifts = 0;
    int i = 0;
    hipotese.cords = casas;
    if (hipotese.cords.direcao == 'H')
    {
        for (hipotese.comprimento = lado_tab; hipotese.comprimento >= 2; hipotese.comprimento--)
        {
            numero_shifts = lado_tab - hipotese.comprimento;
            for (hipotese.cords.coluna = 0; hipotese.cords.coluna <= numero_shifts; hipotese.cords.coluna++)
            {
                init_local_palavra_algoritmo(matriz_tab, hipotese.cords.coluna, hipotese.cords.linha, hipotese.cords.direcao, hipotese.comprimento, local_palavra);
                if (hipotese.cords.coluna <= casas.coluna && (hipotese.cords.coluna + hipotese.comprimento) >= casas.coluna)
                {
                    // testestar todas as palavras com o comprimento hipotetico
                    for (i = 0; i < linhas_dicionario; i++)
                    {
                        if (strlen(linha_dic[i]) == hipotese.comprimento)
                        {
                            hipotese.pontos = calcular_pontos_jogada(local_palavra, linha_dic[i], hipotese.comprimento);
                            if (hipotese.pontos > jogada.pontos)
                            {
                                if (validar_palavra(local_palavra, hipotese, lado_tab, local_palavra))
                                {
                                    strcpy(hipotese.palavra, linha_dic[i]);
                                    hipotese.pontos = calcular_pontos_jogada(local_palavra, linha_dic[i], hipotese.comprimento);
                                    jogada = hipotese;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (hipotese.cords.direcao == 'V')
    {
        for (hipotese.comprimento = lado_tab; hipotese.comprimento >= 2; hipotese.comprimento--)
        {
            numero_shifts = lado_tab - hipotese.comprimento;
            for (hipotese.cords.coluna = 0; hipotese.cords.coluna <= numero_shifts; hipotese.cords.coluna++)
            {
                init_local_palavra_algoritmo(matriz_tab, hipotese.cords.coluna, hipotese.cords.linha, hipotese.cords.direcao, hipotese.comprimento, local_palavra);
                if (hipotese.cords.coluna <= casas.coluna && (hipotese.cords.coluna + hipotese.comprimento) >= casas.coluna)
                {
                    // testestar todas as palavras com o comprimento hipotetico
                    for (i = 0; i < linhas_dicionario; i++)
                    {
                        if (strlen(linha_dic[i]) == hipotese.comprimento)
                        {
                            hipotese.pontos = calcular_pontos_jogada(local_palavra, linha_dic[i], hipotese.comprimento);
                            if (hipotese.pontos > jogada.pontos)
                            {
                                if (validar_palavra(local_palavra, hipotese, lado_tab, local_palavra))
                                {
                                    strcpy(hipotese.palavra, linha_dic[i]);
                                    hipotese.pontos = calcular_pontos_jogada(local_palavra, linha_dic[i], hipotese.comprimento);
                                    jogada = hipotese;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return jogada;
}

void calcular_casas (char matriz_tab[][LADO_MAX_TAB], int lado_tab, cords casas[])
{
    int k = 0;
    for (int i = 0; i< lado_tab; i++)
    {
        for (int j=0; j < lado_tab; j++)
        {
            if (!ocupacao_local_matriz(matriz_tab[i][j]))
            {
                casas[k].linha= i;
                casas[k].coluna= j;
                k++;
            }
            
        }
    }
}

void init_local_palavra_algoritmo(char matriz_tab[][LADO_MAX_TAB], char coluna, int linha, char direcao, int comprimento, char local_palavra[])
{
    for (int k = 0; k< 10; k++)
    {
        local_palavra[k] = '\0';
    }

    if (direcao == 'H')
    {
        for (int j = coluna; j <= (coluna + comprimento -1); j++)
        {
        local_palavra[j-coluna] = matriz_tab [linha][j];
        }
    }
    if (direcao == 'V')
    {
        for (int i = linha; i <= (linha + comprimento -1); i++)
        {
        local_palavra[i-linha] = matriz_tab [i][coluna];
        }
    }
}

bool validar_palavra (char linha_palavra[], Info2 hipotese, int lado_tab, char local_palavra[])
{
    bool flag = true;
    bool letra_comum = false;


    //verifica se as palavras são iguais
    if (strcmp(local_palavra, hipotese.palavra) == 0) flag= false;

    for (int i=0; i<hipotese.comprimento;i++)
    {
        if(local_palavra[i] == hipotese.palavra[i])
        {
            letra_comum = false;
        }
        else
        {
            //verificar se é uma letra ou um caracter do tabuleiro
            if(((int)local_palavra[i] > 96 && (int)local_palavra[i] <= (123)))
                flag = false; 
        }
    }
    if (!letra_comum) flag = false;

    return flag;
}

int valor_letra (char letra)
{
  int retval=0;
  char value1[] = "aeilnorstu";
  char value2[] = "dg";
  char value3[] = "bcmp";
  char value4[] = "fhvwy";
  char value5[] = "k";
  char value8[] = "jx";
  char value10[] = "qz";
  
  int valret=0;

  if(strchr(value1, letra) != NULL) {valret=1;}
  if(strchr(value2, letra) != NULL) {valret=2;}
  if(strchr(value3, letra) != NULL) {valret=3;}
  if(strchr(value4, letra) != NULL) {valret=3;}
  if(strchr(value5, letra) != NULL) {valret=5;}
  if(strchr(value8, letra) != NULL) {valret=8;}
  if(strchr(value10, letra) != NULL) {valret=10;}

  return valret;
}

int calcular_pontos_jogada (char local_palavra[], char palavra[], int comprimento_palavra)
{
    int multiplicadores[comprimento_palavra];
    int pontos_letras[comprimento_palavra];
    int vale_dobro = 0;

      for (int i=0; i < comprimento_palavra; i++)
    {
        if (local_palavra[i] == '2') multiplicadores[i] = 2;
        else if (local_palavra[i] == '3') multiplicadores[i] = 3;
        else if (local_palavra[i] == '$') 
        {
            vale_dobro++;
            multiplicadores[i] = 1;
        }
        else  multiplicadores[i] = 1;
    }
     
     for (int i=0; i < comprimento_palavra; i++)
    {
       pontos_letras[i] = valor_letra (palavra[i]);
    }

    int pontos_multiplicados = 0;

    for (int i=0; i < comprimento_palavra; i++)
    {
       pontos_multiplicados += (pontos_letras[i] * multiplicadores[i]);
    }
    int dobro= (vale_dobro * 2);
    if (dobro == 0) dobro =1;

    return pontos_multiplicados * dobro;
}

void print_palavra (char matriz_tab[][LADO_MAX_TAB], char palavra[], int  coluna, int linha, char direcao, int lado_tab)
{
    int comprimento_palavra = strlen(palavra);
    if (direcao == 'H')
    {
        for (int j = (coluna); j < (coluna + comprimento_palavra); j++)
        {
        matriz_tab [linha][j] = palavra[j-coluna];
        }
    }
    if (direcao == 'V')
    {
        for (int i = linha; i < (linha + comprimento_palavra); i++)
        {
        matriz_tab [i][coluna] = palavra[i - linha];
        }
    }
    
}



