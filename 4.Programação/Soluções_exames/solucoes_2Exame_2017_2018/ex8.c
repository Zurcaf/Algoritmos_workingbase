#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_STRING 1000
#define MAX_COLS 10
#define MAX_ROWS 10

void ler_ficheiro(const char filename[], int mat[MAX_ROWS][MAX_COLS], int *nlins, int *ncols)
{
    char line[MAX_STRING], *pLine = NULL;
    FILE *myfile = NULL;
    int ret, val, j = 0, i = 0;

    *nlins = -1;
    *ncols = -1;
    // open file
    myfile = fopen ( filename, "r" );
    if (myfile == NULL) {
        printf("Cannot open file\n");
        exit(EXIT_FAILURE);
    }
    // ...
    for ( i = 0; i < MAX_ROWS; i++ )
        for ( j = 0; j < MAX_COLS; j++ )
            mat[i][j] = 0;

    // read it !
    while ( fgets(line, MAX_STRING, myfile) )
    {
        ret = sscanf(line, "mat(%d,%d) = %d\n",&i,&j,&val);
        if ( ret == 3 ) {
            mat[i][j] = val;
            if ( i > *nlins ) *nlins = i;
            if ( j > *ncols ) *ncols = j;
        }
    }
    *nlins +=1;
    *ncols +=1;
    // close it
    fclose(myfile);
}

void substitui(int mat[MAX_ROWS][MAX_COLS], int nlins, int ncols)
{
    int sum=0, ii=0, jj=0, mat_aux[MAX_ROWS][MAX_COLS]={{0}};

    for ( ii = 1; ii < nlins - 1; ii++ ) {
        for ( jj = 1; jj < ncols - 1; jj++ ) {
            sum =  (mat[ii-1][jj] + mat[ii+1][jj] + mat[ii][jj-1] + mat[ii][jj+1])/4.0f;
            mat_aux[ii][jj] = sum;
        }
    }

    for ( ii = 0; ii < nlins; ii++ ) {
        for ( jj = 1; jj < ncols; jj++ ) {
            mat_aux[ii][jj] = mat[ii][jj];
        }
    }
}

void magic_square(int matrix[MAX_ROWS][MAX_COLS], int nlins) 
{
    int i = 0, row=0, column=0;

    int *data = (int *)calloc((2*nlins+1), sizeof(int));

    for (row = 0; row < nlins; row++) {
        for (column = 0; column < nlins; column++) {
            data[row] += matrix[row][column];
            data[nlins + column] += matrix[column][row];
            if ( row == column)
                data[2*nlins] += matrix[row][column];
        }
    }

    for ( i = 1; i < 2*nlins+1; i++ ){
        if( (data[i] - data[i-1]) != 0 ){
            printf("Not magic ! %d, %d %d\n", i, data[i], data[i-1]);
            return;
        }
    }
    printf("Magic!");
    free(data);
}


void print_mat(int mat[][MAX_COLS], int nlin, int ncols )
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
    static const char filename[] = "magic.txt";
    int mat[MAX_ROWS][MAX_COLS] = {{0}};
    int nlins = 0, ncols = 0;
    
    ler_ficheiro( filename, mat, &nlins, &ncols);
    print_mat(mat, nlins, ncols);
    magic_square(mat, nlins);

    return EXIT_SUCCESS;
}
