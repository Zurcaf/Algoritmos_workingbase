#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "headers/3-fileStats.h"

// void getStats(char *locationStat, int *lenCount)
void getStats(char *locationStat)
{
    int *lenCount;
    FILE *palsPointer;

        // abrir o ficheiro e verificar se foi aberto com sucesso
    palsPointer = (FILE *)fopen(locationStat, "r");
    if (palsPointer == (FILE *)NULL)
    {
        fprintf(stderr, "File %s cannot be read.  Please correct.\n", locationStat);
        exit(0);
    }

    char word[40]; // buffer para a palavra
    
    // int i, j;
}