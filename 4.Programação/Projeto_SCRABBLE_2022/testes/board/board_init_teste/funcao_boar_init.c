#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


int main(){

    int board_side = 15;
    char nome_ficheiro_tab[] = "15x15-vazio.txt";
    char matriz_tab[40][40];

    FILE *file_tab;
    char board_line[300];
    char *result;

    char delimitador[] = " ";

    char *temp_line[300];
    int i = 0;
    int board_colun = 0, line_track = 0;

    file_tab = fopen(nome_ficheiro_tab, "r");
    if (file_tab == NULL)
    {
        printf("Problemas na abertura do ficheiro onde se encontra o tabuleiro (%s)\n", nome_ficheiro_tab);
    }
    while (!feof(file_tab))
    {
        if (fgets(board_line, 100, file_tab))
        {
            char *ptr_linha = strtok(board_line, delimitador);
            while (ptr_linha != NULL)
            {
                temp_line[i++] = ptr_linha;
                ptr_linha = strtok(NULL, delimitador);
            }
            line_track++;
            for (int board_colun = 1; board_colun < (board_side + 1); board_colun++)
            {
                matriz_tab[line_track][board_colun] = *temp_line[board_colun];
            }
        }
    }
    fclose(file_tab);
}