#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// inicializa a matriz_board com os caracteres do fichero descartando os numeros
// e letras das coordenadas para matrix_board ser 15x15 e ocupar menos memoria
bool board_init(char matriz_tab[][15], char nome_ficheiro_tab[], int lado_tabuleiro);

// imprime o vetor matriz_board guardado e os numeros e letras de coordenadas
void print_board(char matriz_tab[][15], int lado_tab);

// verifica se é a primeira jogada ou não
bool check_first(char matriz_tab[][15], int lado_tab);

// converte strings em maiusculas
void toupper_conversion(char string[]);
// converte strings em minusculas
void tolower_conversion(char string[]);

// verifica se é para terminar o jogo
bool check_end(char todas_coordenadas[]);

// verifica se as coordenadas linha e coluna são validas
bool check_coords(char todas_coordenadas[], int lado_tab);

// verifica se a jogada é valida
bool check_play(char matriz_tab[][15], char palavra[], char todas_coordenadas[], int lado_tab, int comprimento, bool primeira_jogada);

// substitui os caracteres das coordenas por numeros inteiros
void int_coordinates(char coordenadas_char[], int *coordenadas_int[], int lado_tab);

// escreve a palavra no tabuleiro
bool right_word(char matriz_tab[][15], char palavra[], char coluna, char linha, char direcao, int comprimento);

// roda o tabuleiro 90 graus para a esquerda
//(inverte linhas e depois faz a transposta)
void rotated_board_init(char matriz_tab[][15], char tab_rodado[][15], int lado_tab);

int main()
{
    int board_side = 15;
    char board_file_name[] = "tabs_vazios/15x15-vazio.txt";

    char matrix_board[board_side][board_side];

    int length;
    char all_coordinates[3];
    char word[board_side];
    char line_coordinate;
    char colun_coordinate;
    char direction;
    char erro_message[100];

    if (board_init(matrix_board, board_file_name, board_side))
    {
        printf("Problemas na abertura do ficheiro onde se encontra o tabuleiro (%s)\n", board_file_name);
        return 12;
    }

    print_board(matrix_board, board_side);

    do
    {
        bool first_play = check_first(matrix_board, board_side);

        printf("Insira a sua jogada: ");
        scanf("%s", all_coordinates);

        if (check_coords(all_coordinates, board_side))
                printf("O par coordenadas coluna/linha não é valido\nInsira novamente\n");
        else
        {     
        toupper_conversion(all_coordinates);

        colun_coordinate = all_coordinates[0];
        line_coordinate = all_coordinates[1];
        direction = all_coordinates[2];

        if (check_end(all_coordinates))
        {

            scanf("%s", word);
            tolower_conversion(word);
            length = strlen(word);

            printf("\nColuna:%c linha:%c Direção:%c  ", colun_coordinate, line_coordinate, direction);
            printf("palavra: %s \n", word);

            if (direction != 'H' && direction != 'V')
                printf("Por favor coloque um valor valido na terceira cordenada(direção):\n -> V (vertical)\n -> H (horizontal)\n");
        //     else if (check_play(matrix_board, word, all_coordinates, board_side, length, first_play))
        //         printf("Por favor tente outra palavra");
        //     else
        //     {
        //         printf("substituir palavra na matriz \nImprimir matriz \n imprimr coordenadas e palavra \nimprimir pontos ");
        //     }
        }
        else
        {
            printf("Fim do jogo\n");
            printf("imprimir total de pontos\n");
        }
        }
    } while (check_end(all_coordinates));

    return 0;
}

    bool board_init(char matriz_tab[][15], char nome_ficheiro_tab[], int lado_tab)
    {
        // matriz aumentada é porque o ficheiro tem tambem os numeros e letras
        // assim lemos tudo e depois descarta-se o que nao é preciso
        int lado_m_aumentada = lado_tab + 1;
        char matriz_aumentada[lado_m_aumentada][lado_m_aumentada];

        char *linha_separada[lado_tab];

        FILE *file_tab;
        char linha_ficheiro[100];

        // verifica se consegue abrir o ficheiro do tabuleiro
        file_tab = fopen(nome_ficheiro_tab, "r");
        if (file_tab == NULL)
            return true;

        char delimitador[] = " ";
        int linha_m_aumentada = 0, coluna_m_aumentada;
        while (!feof(file_tab))
        {
            coluna_m_aumentada = 0;
            if (fgets(linha_ficheiro, 100, file_tab))
            {
                // divide cada linha lida em tokens
                int i = 0;
                char *ptr_linha = strtok(linha_ficheiro, delimitador);
                while (ptr_linha != NULL)
                {
                    linha_separada[i++] = ptr_linha;
                    ptr_linha = strtok(NULL, delimitador);
                }
            }
            // coloca cada token numa linha da matriz aumentada
            for (coluna_m_aumentada = 0; coluna_m_aumentada < lado_m_aumentada; coluna_m_aumentada++)
            {
                matriz_aumentada[linha_m_aumentada][coluna_m_aumentada] = *linha_separada[coluna_m_aumentada];
            }
            linha_m_aumentada++;
        }
        fclose(file_tab);

        // tranferencia dos caracteres que variam para o tabuleiro

        for (linha_m_aumentada = 0; linha_m_aumentada < lado_tab; linha_m_aumentada++)
        {
            for (coluna_m_aumentada = 0; coluna_m_aumentada < lado_tab; coluna_m_aumentada++)
            {
                matriz_tab[linha_m_aumentada][coluna_m_aumentada] = matriz_aumentada[linha_m_aumentada][coluna_m_aumentada + 1];
            }
        }
        return false;
    }

    void print_board(char matriz_tab[][15], int lado_tab)

    {
        int linha = 0, coluna = 0;
        char letra = 'A';

        for (linha = 0; linha < lado_tab; linha++)
        {
            if (linha < 9)
                printf(" ");
            printf("%d", linha + 1);
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

    bool check_first(char matriz_tab[][15], int lado_tab)
    {
        int i = 0;
        int quantidade_letras = 26;
        char qualquer_letra = 'a';
        bool flag = true;

        for (i = 0; i < quantidade_letras; i++)
        {
            if (matriz_tab[((lado_tab)/2)][((lado_tab)/2)] == qualquer_letra)
            {
                flag = false;
                i = quantidade_letras;
            }
            else
            {
                qualquer_letra += 1;
            }
        }
        return flag;
    }

    void toupper_conversion(char string[])
    {
        int i = 0;
        char caracter_aux;
        while (string[i])
        {
            caracter_aux = toupper(string[i]);
            string[i] = caracter_aux;
            i++;
        }
    }
    void tolower_conversion(char string[])
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

    bool check_end(char todas_coordenadas[])
    {
        bool flag = true;
        if (todas_coordenadas[0] != 'F' || todas_coordenadas[1] != 'I' || todas_coordenadas[2] != 'M')
            flag = false;
        if (todas_coordenadas[0] != 'f' || todas_coordenadas[1] != 'i' || todas_coordenadas[2] != 'm')
            flag = false;
        return flag;
    }

    bool check_coords(char todas_coordenadas[], int lado_tab)
    {
        int i = 0;
        char numero_linha=todas_coordenadas[1];
        char letra_coluna=todas_coordenadas[0];
        char numeros_possiveis = '1';
        char letras_possiveis = 'A';
        char letras_minusculas_possiveis = 'a';
        
        bool flag = true;
        bool linha = true;
        bool coluna = true;
        bool coluna_linha = true;

        bool fim = (check_end(todas_coordenadas));
        for (i = 0; i < lado_tab; i++)
        {
            if (numero_linha == numeros_possiveis)
            {
                linha = false;
            }
            else
                numeros_possiveis += 1;

            if (letra_coluna == letras_possiveis)
            {
                coluna = false;
            }
            else
                letras_possiveis += 1;
            if (letra_coluna == letras_minusculas_possiveis)
            {
                coluna = false;
            }
            else
                letras_minusculas_possiveis += 1;
        }

        coluna_linha = (linha || coluna);
        flag = (coluna_linha || fim);
        return flag;
    }

    bool check_play (char matriz_tab[][15], char palavra[], char todas_coordenadas[], int lado_tab, int comprimento, bool primeira_jogada)
    {
        int *coordenadas_int[2];

        int_coordinates(todas_coordenadas, & *coordenadas_int, lado_tab);
        printf("\nno check_play \nColuna:%d linha:%d\n", *coordenadas_int[0], *coordenadas_int[1]);
        
        if (primeira_jogada)
        {
            // if (direcao != 'H')
            //     printf("A primeira palavra tem de ser horizontal");
            
            // char_to_int (todas_coordenadas);

        }
        else
        {

        }
        
        // char board_rotated [board_side][board_side];
        // rotated_board_init (matrix_board, board_rotated, board_side);
        // print_board(board_rotated, board_side);
    }

    void int_coordinates (char coordenadas_char[], int *coordenadas_int[], int lado_tab)
    {
        int i = 0;
        char numeros_possiveis = '1';
        char letras_possiveis = 'A';

        for (i = 1; i < lado_tab+1; i++)
        {
            if (coordenadas_char[1] == numeros_possiveis)
            {
                *(*coordenadas_int + 1) = i;
            }
            else
                numeros_possiveis += 1;

            if (coordenadas_char[0] == letras_possiveis)
            {
                *(*coordenadas_int) = i;
            }
            else
                letras_possiveis += 1;
        }
    }

    bool right_word(char matriz_tab[][15], char palavra[], char coluna, char linha, char direcao, int comprimento)
    {
        
        
        // int i = 0;

        // for (i=0; i<)
        // {

        // }
    }

    void rotated_board_init(char matriz_tab[][15], char tab_rodado[][15], int lado_tab)
    {
        char matriz_aux[lado_tab][lado_tab];
        int i = 0, j = 0, k;
        k = (lado_tab - 1);
        for (i = 0; i < lado_tab; i++)
        {
            for (j = 0, k = (lado_tab - 1); j < lado_tab, k >= 0; j++, k--)
            {
                matriz_aux[i][j] = matriz_tab[i][k];
            }
        }

        printf("\n");
        char linha[lado_tab];
        i = 0;
        j = 0;

        for (i = 0; i < lado_tab; i++)
        {
            for (j = 0; j < lado_tab; j++)
            {
                linha[j] = matriz_aux[i][j];
                tab_rodado[j][i] = linha[j];
            }
        }
    }