#include <stdio.h>
#include <stdlib.h>

int main ( void ){
    int **arr;

    arr = (int **) malloc(100*sizeof(int *));

    free(arr);

    return EXIT_SUCCESS;

}
