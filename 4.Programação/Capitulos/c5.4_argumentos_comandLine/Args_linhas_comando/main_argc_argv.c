#include <stdio.h>

int main(int argc, char *argv[]){
    int i;

    printf("O programa tem %d argumentos.\n\n", argc);
    
    for (i=0; i<argc; i++){
        printf ("Argumento %d: %s\n", i, argv[i]);
    }

    if (argc == 1){
        printf("O programa corre sem argumentos!!!\n");
    }else if(argc != 1){
    
    }
    return 0;
}