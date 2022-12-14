#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//coloca o tabuleiro do ficheiro no computador
void init_tabuleiro(char nome_ficheiro[], char matriz_tab[][15], int lado_tab);

//confirmar se o tabuleiro está no formato correto
bool validar_tabuleiro (char matriz_tab[][15], int lado_tab, bool *ptr_primeira_jogada);

//imprimir o tabuleiro
void print_tabuleiro(char matriz_tab[][15], int lado_tab);

// verificar se é a primeira jogada
bool verificar_primeira(char matriz_tab);

//verificar se termina o jogo
bool verificar_fim(char jogada[]);

bool verif_coluna (char coluna, int lado_tab);
bool verif_linha (int linha, int lado_tab);
bool verif_direcao (char direcao);

bool numero_digitos_linha (char jogada[]);

bool validar_coordenadas (char jogada[], char *coluna, int *linha, char *direcao, int lado_tab);

struct 
{
char jogada;

char coluna;
int linha;
char direcao;

char palavra;
}instrucoes;



struct
{
char palavra [16];
char boad [16];

int multiplicadores[16];
int pontos_letras[16];
int pontos_palavra;

bool vale_dobro;
bool local_proibido;
}palavra; 



int main ()
{
int lado_tab=15;
char ficheiro_tab[] = "tabs_vazios/15x15-vazio.txt";


bool primeira_jogada= false;
bool fim = false;

char matriz_tab[lado_tab][lado_tab];

char jogada[30];
char coluna;
int linha;
char direcao;

char palavra[21];


init_tabuleiro(ficheiro_tab, matriz_tab, lado_tab);
if (validar_tabuleiro(matriz_tab, lado_tab, &primeira_jogada)) return EXIT_FAILURE; 

print_tabuleiro(matriz_tab, lado_tab);

do
{
    printf("Insira a sua jogada: ");
    fgets(jogada, 30, stdin);

    if (verificar_fim(jogada))
    {
        printf ("Total de pontos:\nFim do jogo.\n");
        return EXIT_FAILURE;
    }

if (validar_coordenadas (jogada, &coluna, &linha, &direcao, lado_tab)) fim = false;
printf("%c %d %c\n", coluna, linha, direcao);
}
while (fim);

return EXIT_SUCCESS;
}


void init_tabuleiro(char nome_ficheiro[], char matriz_tab[][15], int lado_tab)
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

bool validar_tabuleiro(char matriz_tab[][15], int lado_tab, bool *ptr_primeira_jogada)
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
                    if (verificar_primeira(matriz_tab[7][7]))
                    {
                        *ptr_primeira_jogada = true;
                    }
                    else
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

void print_tabuleiro(char matriz_tab[][15], int lado_tab)

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
}

bool verificar_primeira(char centro)
{
    int valor_caract;
    valor_caract = (int)centro;
    if (valor_caract > 90 && valor_caract < 123)
        return true;
    else
        return false;
}

bool verificar_fim(char jogada[])
{

    bool flag = false;
    if (jogada[0] == 'F' && jogada[1] == (int)'I' && jogada[2] == 'M')
        flag = true;
    if (jogada[0] == 'f' && jogada[1] == (int)'i' && jogada[2] == 'm')
        flag = true;
    
    return flag;
}

bool verif_coluna (char coluna, int lado_tab)
{
    if (((int) coluna > 64 && (int)coluna <= (64+lado_tab)) || ((int)coluna > 94 && (int)coluna <= (94 + lado_tab))) return false;
}

bool verif_linha (int linha, int lado_tab)
{
if (linha > 0 && linha <= lado_tab) return false;
}

bool verif_direcao (char direcao)
{
if (direcao == 'h' || direcao == 'H' || direcao == 'v' || direcao == 'V') return false;
}

bool validar_coordenadas (char jogada[], char *coluna, int *linha, char *direcao, int lado_tab)
{
bool flag = false;

if (jogada[3] == ' ')
{
    *coluna = jogada[0];
    *linha = ((int)jogada[1]-48);
    *direcao = jogada[2];
    
    if (verif_coluna (*coluna, lado_tab))
    {
        printf ("ERRO: coluna\n");
        flag = true;
    }
    if (verif_linha (*linha, lado_tab))
    {
        printf ("ERRO: linha\n");
        flag = true;
    }
    if (verif_direcao (*direcao))
    {
        printf ("ERRO: direção\n");
        flag = true;
    }
}
else if (jogada[4] == ' ')
{
*coluna = jogada[0];
*linha = ((int)jogada[1]-48)*10+((int)jogada[2]-48);
*direcao = jogada[3];

   if (verif_coluna (*coluna, lado_tab))
    {
        printf ("ERRO: coluna\n");
        flag = true;
    }
    if (verif_linha (*linha, lado_tab))
    {
        printf ("ERRO: linha\n");
        flag = true;
    }
    if (verif_direcao (*direcao))
    {
        printf ("ERRO: direção\n");
        flag = true;
    }
}
else printf("jogada invalida\n");

*coluna = toupper(*coluna);
*direcao = toupper (*direcao);

return flag;
}

