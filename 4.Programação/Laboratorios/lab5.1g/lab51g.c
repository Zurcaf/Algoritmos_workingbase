#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numLinhas 141
#define num_escaloes 10

void contarChars(FILE *, int [numLinhas], char *[numLinhas]);
void reordena (FILE *, char *[numLinhas], char * [numLinhas]);
void libertaMem (char *[numLinhas]);


int main (void)
{ 
    FILE *fp;
    FILE *fp_out;
    int numChars [numLinhas] = {0};
    char *linhas[numLinhas] = {NULL};
    char *linha_ord[numLinhas] = {NULL};

    fp = fopen("braga17.txt", "r");

    if( fp == NULL)
    {
        printf("Impossivel abrir o ficheiro!");
        exit(EXIT_FAILURE);
    }
    fp_out = fopen("braga17_out.txt", "w");
    if( fp_out == NULL)
    {
        printf("Impossivel abrir o ficheiro!");
        exit(EXIT_FAILURE);
    }
    /*while((char = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }*/
    contarChars(fp, numChars, linhas);
    reordena(fp_out, linhas, linha_ord);
    libertaMem(linhas);
    fclose(fp);
    fclose(fp_out);
    return EXIT_SUCCESS;
}



void contarChars(FILE *_fp, int _numChars[numLinhas], char * _linhas[numLinhas])
{
    int nlinha = 0;
    
    char buffer[200];

    while(fgets(buffer, 200, _fp))
    {
        _numChars[nlinha] = strlen(buffer);
        //printf("\n Linha %d : %d chars \n",nlinha,_numChars[nlinha]);
        _linhas[nlinha] = ((char*) calloc((_numChars[nlinha]), sizeof(char)));
        if (_linhas[nlinha] == NULL)
        {
            printf("Falha na alocação de memória");
            exit(EXIT_FAILURE);
        }
        strcpy(_linhas[nlinha],buffer);
        //printf("%p\n", _linhas[nlinha]);
        //puts(_linhas[nlinha]);
        nlinha++;
    }
}

void reordena(FILE * _fp_out, char * _linhas[numLinhas], char * _linha_ord[numLinhas])
{
    char escaloes[10][4] = {{'\0'}};
    int i = 0, j = 0, linha = 0;

    for ( i = 0 ; i < numLinhas; i++)
    {
        switch (i)
        {
            case 1:
            strcpy(escaloes[i-1], "F20");
            break;
            case 2:
            strcpy(escaloes[i-1], "F40");
            break;
            case 3:
            strcpy(escaloes[i-1], "F45");
            break;
            case 4:
            strcpy(escaloes[i-1], "M20");
            break;
            case 5:
            strcpy(escaloes[i-1], "M35");
            break;
            case 6:
            strcpy(escaloes[i-1], "M40");
            break;
            case 7:
            strcpy(escaloes[i-1], "M45");
            break;
            case 8:
            strcpy(escaloes[i-1], "M50");
            break;
            case 9:
            strcpy(escaloes[i-1], "M55");
            break;
            case 10:
            strcpy(escaloes[i-1], "M60");
            break;
        }
    }
    for(i = 0; i < num_escaloes; i++)
    {
        for(j = 0; j < numLinhas; j++)
        {
            if((strstr(_linhas[j],escaloes[i])) != NULL) 
            {
                _linha_ord[linha] = _linhas[j];
                //puts(_linha_ord[linha]);
                fprintf(_fp_out, (_linha_ord[linha]));
                linha++;
            }

        }
    }
}

void libertaMem(char * _linhas[numLinhas])
{
    int i = 0;

    for (i = 0; i < numLinhas; i++)
    {
        free(_linhas[i]);
    }
}