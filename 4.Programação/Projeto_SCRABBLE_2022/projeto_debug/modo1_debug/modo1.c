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
    char coluna;
    int linha;
    char direcao;
} cords;

typedef struct Info
{
    char cords_palavra[100];
    cords cords;
    char palavra[50];
    int pontos;
} Info;

//inicializa o tabuleiro vazio
void init_tabuleiro_vazio(char matriz_tab[][LADO_MAX_TAB], int lado_tab);

//coloca o tabuleiro do ficheiro no computador
void init_tabuleiro_file(char nome_ficheiro[], char matriz_tab[][LADO_MAX_TAB], int lado_tab);

//confirmar se o tabuleiro está no formato correto
bool validar_tabuleiro (char matriz_tab[][LADO_MAX_TAB], int lado_tab);

//imprimir o tabuleiro
void print_tabuleiro(char matriz_tab[][LADO_MAX_TAB], int lado_tab);

// verificar se é a primeira jogada
bool ocupacao_local_matriz(char centro);

//verificar se termina o jogo
bool verificar_fim(char jogada[]);

bool verif_coluna (char coluna, int lado_tab);
bool verif_linha (int linha, int lado_tab);
bool verif_direcao (char direcao);

bool numero_digitos_linha (char jogada[]);

void separar_jogada(char jogada[], char coordenadas[], char palavra[]);

bool validar_coordenadas (char jogada[], char *coluna, int *linha, char *direcao, int lado_tab);

bool verificar_palavra (char palavra[]);

void conversao_tolower(char string[]);

void init_linha_palavra(char matriz_tab[][LADO_MAX_TAB], char coluna, int linha, char direcao, int lado_tab, char lado_palavra[]);

void init_local_palavra(char local_palavra[], char linha_palavra[], int comprimento_palavra);

bool validar_primeira (char comprimento_palavra, char palavra[], char coluna, int linha, char direcao, int lado_tab);

bool validar_palavra_primeira (char linha_palavra[], char palavra[], int lado_tab, int comprimento_palavra, char local_palavra[]);

bool validar_palavra (char linha_palavra[], char palavra[], int lado_tab, int comprimento_palavra, char local_palavra[]);

int valor_letra (char letra);

int calcular_pontos_jogada (char local_palavra[], char palavra[], int comprimento_palavra);

void print_palavra (char matriz_tab[][LADO_MAX_TAB], char palavra[], char coluna, int linha, char direcao, int lado_tab);


int main()
{
    int lado_tab = 9;
    bool tab_file = false;
    char ficheiro_tabuleiro_inicio[] = "jkenwejk";

    bool validade = true;
    bool impossivel = false;

    char matriz_tab[LADO_MAX_TAB][LADO_MAX_TAB];
    char linha_palavra[LADO_MAX_TAB] = {'\0'};
    char local_palavra[LADO_MAX_TAB] = {'\0'};

    int comprimento_palavra;
    int pontos_totais = 0;

    int numero_jogada = 0;

    if (tab_file)
    {
        init_tabuleiro_file(ficheiro_tabuleiro_inicio, matriz_tab, lado_tab);
        if (validar_tabuleiro(matriz_tab, lado_tab))
            return 0;
    }
    else
        init_tabuleiro_vazio(matriz_tab, lado_tab);

    do
    {
        Info jogada;
        do
        { 
            validade = true;
            print_tabuleiro(matriz_tab, lado_tab);
            printf("Insira a sua jogada: ");
            fgets(jogada.cords_palavra, 100, stdin);

            if (verificar_fim(jogada.cords_palavra))
            {
                printf("Total de pontos: %d\nFim do jogo.\n", pontos_totais);
                return EXIT_SUCCESS;
            }

            separar_jogada(jogada.cords_palavra, jogada.cords.coordenadas, jogada.palavra);

            if (validar_coordenadas(jogada.cords.coordenadas, &jogada.cords.coluna, &jogada.cords.linha, &jogada.cords.direcao, lado_tab))
                validade = false;

            if (verificar_palavra(jogada.palavra))
            {
                printf("ERRO: palavra invalida\n");
                validade = false;
            }
            else
            {
                conversao_tolower(jogada.palavra);
            }

            comprimento_palavra = strlen(jogada.palavra);

            init_linha_palavra(matriz_tab, jogada.cords.coluna, jogada.cords.linha, jogada.cords.direcao, lado_tab, linha_palavra);
            init_local_palavra(local_palavra, linha_palavra, comprimento_palavra);

            if (ocupacao_local_matriz(matriz_tab[lado_tab/2][lado_tab/2]))
            {
                if (validar_palavra_primeira(linha_palavra, jogada.palavra, lado_tab, comprimento_palavra, local_palavra))
                {
                    printf("Erro: jogada invalida\n\n");
                    validade = false;
                    continue;
                }
                if (validar_primeira(comprimento_palavra, jogada.palavra, jogada.cords.coluna, jogada.cords.linha, jogada.cords.direcao, lado_tab))
                {
                    printf("Erro: jogada invalida\n\n");
                    validade = false;
                    continue;
                }
            }else {
            if (validar_palavra(linha_palavra, jogada.palavra, lado_tab, comprimento_palavra, local_palavra))
            {
                printf("Erro: jogada invalida\n\n");
                validade = false;
            }
            }
        } while (!validade);

        jogada.pontos = calcular_pontos_jogada(local_palavra, jogada.palavra, comprimento_palavra);
        pontos_totais += jogada.pontos;
        print_palavra(matriz_tab, jogada.palavra, jogada.cords.coluna, jogada.cords.linha, jogada.cords.direcao, lado_tab);
        
        numero_jogada++;
        printf("Jogada %d: %s %s Pontos: %d\n\n", numero_jogada, jogada.cords.coordenadas, jogada.palavra, jogada.pontos);
    } while (!impossivel);
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
    if (((int) coluna > 64 && (int)coluna <= (64+lado_tab)) || ((int)coluna > 96 && (int)coluna <= (96 + lado_tab))) return false;
}
bool verif_linha (int linha, int lado_tab)
{
if (linha > 0 && linha <= lado_tab) return false;
}
bool verif_direcao (char direcao)
{
if (direcao == 'h' || direcao == 'H' || direcao == 'v' || direcao == 'V') return false;
}

void separar_jogada (char jogada[], char coordenadas[], char palavra[])
{
    int i;
    char delim[] = " ";
    char *ptr_linha;
    char *jogada_separada[10] = {NULL};

    char save_jogada[100];
    strcpy (save_jogada, jogada);
    i = 0;
        ptr_linha = strtok(jogada, delim);
        if (ptr_linha == NULL) printf ("ERRO: Precisa inserir uma jogada");
        while (ptr_linha != NULL)
        {
            jogada_separada[i++] = ptr_linha;
            ptr_linha = strtok(NULL, delim);
        }

        strcpy(coordenadas, jogada_separada[0]);
        strcpy(palavra, jogada_separada[1]);
        strcpy(jogada, save_jogada);
        for (i=0; i<100; i++)
        {
            if (jogada[i]=='\n') jogada[i]= '\0';
            if (coordenadas[i]=='\n') coordenadas[i]= '\0';
            if (palavra[i]=='\n') palavra[i]= '\0';
        }
        return;
}

bool validar_coordenadas (char coordenadas[], char *coluna, int *linha, char *direcao, int lado_tab)
{
    bool flag = false;

    if (strlen(coordenadas) == 3)
    {
        *coluna = coordenadas[0];
        if (((int)coordenadas[1] - 48) > 0)
            *linha = ((int)coordenadas[1] - 48);
        else *linha = 0;
        *direcao = coordenadas[2];

        if (verif_coluna(*coluna, lado_tab))
        {
            printf("ERRO: coluna\n");
            flag = true;
        }
        if (verif_linha(*linha, lado_tab))
        {
            printf("ERRO: linha\n");
            flag = true;
        }
        if (verif_direcao(*direcao))
        {
            printf("ERRO: direção\n");
            flag = true;
        }
    }
    else if (strlen(coordenadas) == 4)
    {
        *coluna = coordenadas[0];
        if ((int)coordenadas[1]>48 && ((int)coordenadas[2]<58))
        *linha = ((int)coordenadas[1] - 48) * 10 + ((int)coordenadas[2] - 48);
        else *linha = 0;
        *direcao = coordenadas[3];

        if (verif_coluna(*coluna, lado_tab))
        {
            printf("ERRO: coluna\n");
            flag = true;
        }
        if (verif_linha(*linha, lado_tab))
        {
            printf("ERRO: linha\n");
            flag = true;
        }
        if (verif_direcao(*direcao))
        {
            printf("ERRO: direção\n");
            flag = true;
        }
    }
    else
    {
        printf("jogada invalida\n");
        flag = true;
    }

    if (flag == false)
    {
        *coluna = toupper(*coluna);
        *direcao = toupper(*direcao);
        coordenadas[0] = *coluna;
        if (strlen(coordenadas) == 3) coordenadas[2] = *direcao;
        else if (strlen(coordenadas) == 4) coordenadas[3] = *direcao;
    }

    return flag;
}

bool verificar_palavra (char palavra[])
{
    bool flag = false;
    for (int i = 0; i< strlen(palavra);i++)
    {
    if (!(((int) palavra[i] > 64 && (int)palavra[i] <= (91)) || ((int)palavra[i] > 96 && (int)palavra[i] <= (123)))) flag = true;
    }
    return flag;
}

void conversao_tolower(char string[])
    {
        int i = 0;
        char caracter_aux;
        while (string[i])
        {
            caracter_aux = tolower(string[i]);
            string[i] = caracter_aux;
            i++;
        }
    }

void init_linha_palavra(char matriz_tab[][LADO_MAX_TAB], char coluna, int linha, char direcao, int lado_tab, char linha_palavra[])
{
    linha -= 1;
    coluna -=1;
    for (int k = 0; k<lado_tab; k++)
    {
        linha_palavra[k] = '\0';
    }
    if (direcao == 'H')
    {
        for (int j = ((int)coluna - 64); j < lado_tab; j++)
        {
        if(matriz_tab[linha][j] == '#') 
        {
            j = lado_tab;
            continue;
        }
        linha_palavra[j-((int)coluna-64)] = matriz_tab [linha][j];
        }
    }
    if (direcao == 'V')
    {
        for (int i = linha; i < lado_tab; i++)
        {
        if(matriz_tab[i][(int)coluna-64] == '#') 
        {
            i = lado_tab;
            continue;
        }
        linha_palavra[i-linha] = matriz_tab [i][(int)coluna-64];
        }
    }
}

void init_local_palavra(char local_palavra[], char linha_palavra[], int comprimento_palavra)
{ 
    for (int i=0; i < comprimento_palavra; i++)
    {
        local_palavra[i]= linha_palavra[i];
    }
}

bool validar_primeira (char comprimento_palavra, char palavra[], char coluna, int linha, char direcao, int lado_tab)
{
    bool flag= false;
    int meio_tab = lado_tab/2;
    int i = linha - 1;
    int j = (int)coluna -65;
    
    if (direcao != 'H') flag = true;
    if (i != meio_tab) flag = true;
    if (j > meio_tab) flag = true;
    else 
    {
        if(j + comprimento_palavra <= meio_tab) flag = true;
    }
return flag;
}

bool validar_palavra_primeira (char linha_palavra[], char palavra[], int lado_tab, int comprimento_palavra, char local_palavra[])
{
    bool flag = false;
    bool letra_comum = false;

    //verifica comprimento da palavra no espaço disponivel
    if (strlen(palavra) > strlen(linha_palavra)) 
    {
        flag=true;
        return flag;
    }

    //verifica se as palavras são iguais
    if (strcmp(local_palavra, palavra) == 0) flag= true;

    for (int i=0; i<comprimento_palavra;i++)
    {
        if(local_palavra[i] == palavra[i])
        {
            
        }
        else
        {
            //verificar se é uma letra ou um caracter do tabuleiro
            if(((int)local_palavra[i] > 96 && (int)local_palavra[i] <= (123)))
                flag = true; 
        }
    }

    return flag;
}

bool validar_palavra (char linha_palavra[], char palavra[], int lado_tab, int comprimento_palavra, char local_palavra[])
{
    bool flag = false;
    bool letra_comum = false;

    //verifica comprimento da palavra no espaço disponivel
    if (strlen(palavra) > strlen(linha_palavra)) 
    {
        flag=true;
        return flag;
    }

    //verifica se as palavras são iguais
    if (strcmp(local_palavra, palavra) == 0) flag= true;

    for (int i=0; i<comprimento_palavra;i++)
    {
        if(local_palavra[i] == palavra[i])
        {
            letra_comum = true;
        }
        else
        {
            //verificar se é uma letra ou um caracter do tabuleiro
            if(((int)local_palavra[i] > 96 && (int)local_palavra[i] <= (123)))
                flag = true; 
        }
    }
    if (!letra_comum) flag = true;

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

void print_palavra (char matriz_tab[][LADO_MAX_TAB], char palavra[], char coluna, int linha, char direcao, int lado_tab)
{
    linha -= 1;
    coluna -=1;
    int comprimento_palavra = strlen(palavra);
    if (direcao == 'H')
    {
        for (int j = ((int)coluna - 64); j < (((int)coluna - 64) + comprimento_palavra); j++)
        {
        matriz_tab [linha][j] = palavra[j-((int)coluna-64)];
        }
    }
    if (direcao == 'V')
    {
        for (int i = linha; i < (linha + comprimento_palavra); i++)
        {
        matriz_tab [i][(int)coluna-64] = palavra[i - linha];
        }
    }
}

