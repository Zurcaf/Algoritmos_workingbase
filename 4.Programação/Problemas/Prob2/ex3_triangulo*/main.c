#include <stdio.h>

#define MAX_LINHAS 300

int calculo_alt_max (int max_num_linhas);
int verfi_se_triang_cabe(int altura, int altura_maxima);
void init_vetor_triang (int max_linhas, char* triangulo[][]);

int main(){
    int alt_triang, max_alt, flag1;
    char triang [MAX_LINHAS][MAX_LINHAS];
    flag1=1;

    do{
    printf("Insira a altura do triangulo: ");
    scanf("%d", &alt_triang);

    max_alt=calculo_alt_max(MAX_LINHAS);
    flag1=verfi_se_triang_cabe(alt_triang, max_alt);
    }while (flag1!=0);

    init_vetor_triang(MAX_LINHAS, &triang);
    //Inicializar o vetor triang
/*
      //Atribuir valores os *'s dos triangulos

    for (i=0; i<linhas; i++){
        for (j=0; j<colunas; j++){
           printf ("%c", triang [i][j]);
        }
        printf("\n");
    }

    //Imprimir o triangulo
*/
    return 0;
}






int calculo_alt_max (int max_num_linhas){
int alt_max= ((max_num_linhas+1)/2);

return alt_max;
}


int verfi_se_triang_cabe(int altura, int altura_maxima){
int flag1=1;
 
    if (altura > altura_maxima){
        printf("Introduziu uma altura invalida\n");
    }
    else if(altura<1){
        printf("Introduziu uma altura invalida\n");
    }
    else {flag1=0;
    }

    return flag1;
}


void init_vetor_triang (int max_num_linhas, char* triangulo[][]){
    int linhas, colunas;
    int i, j;

    linhas = (max_num_linhas);
    colunas = (max_num_linhas);     
    
    for (i=0; i<linhas; i++){
        for (j=0; j<colunas; j++){
           (*triangulo)[i][j]= '*';
        }
    }

}