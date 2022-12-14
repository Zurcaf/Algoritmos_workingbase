#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE 1000
#define NLINHAS 10

int ler_ficheiro(const char filename[], int mat[][12])
{
    char line[MAX_LINE], *pLine = NULL;
    FILE *myfile = NULL;
    int val, i = 0;

    // open file
    myfile = fopen ( filename, "r" );
    if (myfile == NULL) {
        printf("Cannot open file\n");
        exit(EXIT_FAILURE);
    }

    // read it !
    while ( fgets(line, MAX_LINE, myfile) )  // linhas
    {
        val = 0;
        pLine = strtok(line, "#");
        while ( pLine != NULL )
        {
            sscanf( pLine, "%d", &mat[i][val++]);
            pLine = strtok(NULL, "#");
        }
        i++;
    }
    fclose(myfile);
    return i;
}

void maior_aumento(int matriz[][12], int tot_clints, int *maior)
{
    int sum = 0, ii = 0, jj = 0, mes_maior = 0;
    float avgs[12] = {0};
    float max = -1.0;

    for ( ii = 0; ii < 12; ii++ )
    {
        sum = 0;
        for ( jj = 0; jj < tot_clints; jj++ ) {
            sum += matriz[jj][ii];
        }
        avgs[ii] = sum/(float)12;
    }
    for ( ii = 0; ii < 12; ii++ )
    {
        if ( avgs[ii] > max )
        {
            max = avgs[ii];
            *maior = ii;
        }
    }
}

int* por_trimeste(int mat [][12], int ncliente) 
{
    int ii = 0; 
    int *trimestre = (int *)calloc( 4, sizeof(int) );

    if (trimestre == NULL ) exit(EXIT_FAILURE);

    for ( ii = 0; ii < 12; ii++ ) {
        trimestre[ii / 3] += mat[ncliente][ii];
    }
    return trimestre;
}

void meses_crescimento(int mat [][12], int ncliente) 
{
    int ii = 0, periodo = 0;

    for ( ii = 1; ii < 12; ii++) 
    {
        if ( mat[ncliente][ii] > mat[ncliente][ii-1] && !periodo ){
            printf("Intervalo: %d-", ii-1);
            periodo = 1;
        }
        else if ( mat[ncliente][ii] <= mat[ncliente][ii-1] && periodo ) {
            printf("%d\n", ii-1);
            periodo = 0;
        }
    }
    if (periodo) printf("11\n");
}


void print_mat(int mat[][12], int nlin, int ncols )
{
    // print mat: not neeeded in exam
    for ( int ii = 0; ii < nlin; ii++)
    {
        printf("\n");
        for ( int jj = 0; jj < ncols; jj++)
            printf("%d ", mat[ii][jj]);
    }
    printf("\n");
}

int main (void)
{
    static const char filename[] = "leituras.txt";
    int mat[NLINHAS][12] = {{0}};
    int tot_clientes = 0; 
    int *trim = NULL;
    int i = 0, maior = 0;
    
    tot_clientes = ler_ficheiro( filename, mat );
    printf("Total clientes: %d\n", tot_clientes);
    print_mat(mat, tot_clientes, 12);

    //... 
    maior_aumento(mat, tot_clientes, &maior);
    printf("Maior aumento: %d\n", maior);

    trim = por_trimeste(mat, 2);
    printf("%d - %d - %d - %d\n", trim[0], trim[1], trim[2], trim[3]);

    for (i = 0; i < tot_clientes; i++)
    {
        printf("--\n");
        meses_crescimento(mat, i);
    }

    free(trim);
    return EXIT_SUCCESS;
}
