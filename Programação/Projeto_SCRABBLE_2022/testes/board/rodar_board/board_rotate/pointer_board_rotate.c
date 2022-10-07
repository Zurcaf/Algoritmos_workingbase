#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int lado_ma = 9;
int i = 0, j = 0, k = 4;

void init_m1(char[][lado_ma]);
void print_m1(char[][lado_ma]);
void print_m2(long int [][lado_ma]);
//void print_m3(char[][lado_ma]);

void inversao(long int [][lado_ma], long int [][lado_ma]);
void transposta(char[][lado_ma], char [][lado_ma]);

int main()
{

    char m1[lado_ma][lado_ma];
    long int m2[lado_ma][lado_ma];
    char *m3[lado_ma][lado_ma];

    init_m1(m1);
    print_m1(m1);

    printf("\nInversão:\n");

    inversao(&m1, m2);
    print_m2(m2);

    printf("\nTransposta:\n");

    transposta(m2, *m3);
    print_m1(m3);

}

void init_m1(char m[][lado_ma])
{
    for (i = 0; i < lado_ma; i++)
    {
        for (j = 0; j < lado_ma; j++)
        {
            m[i][j] = 'A' + j;
        }
    }
}

void print_m1(char m[][lado_ma])
{
    for (i = 0; i < lado_ma; i++)
    {
        for (j = 0; j < lado_ma; j++)
        {
            printf(" %c", m[i][j]);
        }
        printf("\n");
    }
}

void print_m2(long int m[][lado_ma])
{
    for (i = 0; i < lado_ma; i++)
    {
        for (j = 0; j < lado_ma; j++)
        {
            printf(" %ld", m[i][j]);
        }
        printf("\n");
    }
}

void inversao(long int m1[][lado_ma], long int m2[][lado_ma])
{
    for (i = 0; i < lado_ma; i++)
    {
        for (j = 0, k = (lado_ma-1); j < lado_ma, k >= 0; j++, k--)
        {
            m2[i][j] = m1[i][k];
        }
    }
}

void transposta(char m2[][lado_ma], char m3[][lado_ma])
{
    char linha[lado_ma];
        
    for(i=0; i<lado_ma; i++){
        for (j=0; j<lado_ma; j++){
        linha[j]=m2[i][j];
        m3[j][i]=linha[j];
        }
    }

}