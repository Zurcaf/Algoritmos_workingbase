#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** le_ficheiro(char*, int*);

int main(int argc, char* argv[])
{
    char ** linhas;
    int n_linhas=0;

    linhas = le_ficheiro("RunResults-txt", &n_linhas);
    return EXIT_SUCCESS;
}

char ** le_ficheiro(char* _filename, int *n_linhas){
    //declarar o ficheiro ou variavel do tipo ficheir?
    char ** _linhas;
    FILE * inputfp;
    int lenght;
    char buffer[100];

    //abrir o ficheiro
    if((inputfp= fopen(_filename, "w"))== NULL){
        printf("Erro na leitura do ficheiro\n");
        exit(EXIT_FAILURE);
    }

    //leitura de linha a linha
    *n_linhas = 0;

    while (fgets(buffer, 100,inputfp) != NULL){

        //se nãó é a primeira linha
        if (*n_linhas !=0){
            lenght= strlen(buffer);

            // por segurança se aparecer um \n substituimos por \0
            if(buffer[lenght-1] == '\n') buffer[lenght-1]= '\0';

            if(*n_linhas == 1){
                _linhas=malloc(1*sizeof(char*));
                if(_linhas == NULL){
                    printf("Erro na alocação de memoria\n");
                    exit(EXIT_FAILURE);
                }
            } else{
                _linhas = realloc(_linhas,*n_linhas* sizeof(char*));
                if(_linhas==NULL){
                    printf("Erro na alocação de memoria\n");
                    exit(EXIT_FAILURE);
                }
                }
            //Aloca memoia para a string
            if(_LINHAS[(*n_linhas)-1]= malloc((lenght)+1)* sizeof(char))==NULL{}
        }
    }
    //fechar o ficheiro de texto
    fclose(inputfp);
}
