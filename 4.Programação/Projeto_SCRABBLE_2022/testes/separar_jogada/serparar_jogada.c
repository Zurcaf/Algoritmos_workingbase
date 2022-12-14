#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <getopt.h>

int main()
{
    char jogada[50]= "wknjw wolkw";
    char coordenadas[4];
    char palavra[113];

    int i;
    char delim[] = ' ';
    char *ptr_linha = strtok(jogada, delim);
    char *jogada_separada[10];
    i = 0;
    while (ptr_linha != NULL)
    {
        jogada_separada[i++] = ptr_linha;
        ptr_linha = strtok(NULL, delim);
    }
    strcpy(coordenadas, jogada_separada[0]);
    strcpy(palavra, jogada_separada[1]);

    printf("%s      %s %s",jogada, coordenadas, palavra);
    return 0;
}