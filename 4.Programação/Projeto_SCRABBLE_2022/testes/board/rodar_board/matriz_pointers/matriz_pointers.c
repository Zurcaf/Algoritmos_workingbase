#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int lado_ma =11;
int i = 0, j = 0, k = 4;

void init_m1(char[][lado_ma]);
void print_m(char[][lado_ma]);

void init_mp(char[][lado_ma], char *[][lado_ma]);


int main()
{
    char mt[lado_ma][lado_ma];
    char *mp[lado_ma][lado_ma];
    
    init_m1(mt);
    print_m(mt);

    init_mp(mt, mp);
    print_m(mp);
}


void init_mp (char mt[][lado_ma], char *mp[][lado_ma])
{
    for (i=0; i<lado_ma; i++)
    {
        for (j=0; j<lado_ma; j++)
        {
            mp[i][j] = &mt[i][j];
        }
    }
}









// void inversao(char[][lado_ma], char[][lado_ma]);
// void transposta(char[][lado_ma], char[][lado_ma]);

// int main()
// {

//     char m1[lado_ma][lado_ma];
//     char m2[lado_ma][lado_ma];
//     char m3[lado_ma][lado_ma];

//     init_m1(m1);
//     print_m(m1);

//     printf("\nInversão:\n");

//     inversao(m1, m2);
//     print_m(m2);

//     printf("\nTransposta:\n");

//     transposta(m2, m3);
//     print_m(m3);

// }

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

void print_m(char m[][lado_ma])
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

// void inversao(char m1[][lado_ma], char m2[][lado_ma])
// {
//     for (i = 0; i < lado_ma; i++)
//     {
//         for (j = 0, k = (lado_ma-1); j < lado_ma, k >= 0; j++, k--)
//         {
//             m2[i][j] = m1[i][k];
//         }
//     }
// }

// void transposta(char m2[][lado_ma], char m3[][lado_ma])
// {
//     char linha[lado_ma];
        
//     for(i=0; i<lado_ma; i++){
//         for (j=0; j<lado_ma; j++){
//         linha[j]=m2[i][j];
//         m3[j][i]=linha[j];
//         }
//     }

// }