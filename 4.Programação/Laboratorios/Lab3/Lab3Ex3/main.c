#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VALUES 1000
#define MAX_INTERVAL 10

void gera_amostra (int dimensao, float val[]);
void gera_histograma(int dimensao, float val[], int k, int intervalos[]);
void imprime_histograma (int k, int interval[]);

int main()
{
    int n_valores, n_interval;
    float valores[MAX_VALUES];
    int intervalos[MAX_INTERVAL];
//Gera valores aleatorios
    srand(time(NULL));
//quantidade de valores da amostra
    do{
    printf("Quantos numeros tem a amostra? (1-%d)\n", MAX_VALUES);
    if (scanf("%d", &n_valores)<1){
        printf("Valor nao esta entre 1 e %d", MAX_VALUES);
        return EXIT_FAILURE;
        }
      }while ((n_valores <1) || (n_valores > MAX_VALUES));
//Quantidade de intervalos do histograma
     do{
    printf("Quantos intervalos tem o histograma amostra? (1-%d)\n", MAX_INTERVAL);
    if (scanf("%d", &n_interval)<1){
        printf("Valor nao esta entre 1 e %d", MAX_INTERVAL);
        return EXIT_FAILURE;
        }
      }while ((n_valores <1) || (n_valores > MAX_INTERVAL));


    gera_amostra (n_valores, valores);
    gera_histograma (n_valores, valores, n_interval, intervalos);
    imprime_histograma (n_interval, intervalos);
    return EXIT_SUCCESS;
}


void gera_amostra (int dimensao, float val[]){
    int i;
    //dar valores aleatorios ao vetor com os valores
    for (i=0; i<dimensao; i++){
    val[i]= (float) rand() / RAND_MAX;
    }
    //escreve cada valor escolhido
    for (i=0; i<dimensao; i++){
    printf("%f ", val[i]);
    }
    printf(" ");
    }

void gera_histograma(int dimensao, float val[], int k, int intervalos[]) {
    int i;
    int aux;
    //zerar o vetor dos intervalos
    for (i=0;i< k; i ++){
        intervalos[i]=0;
    }
    //contar a quantidade de valores em cada intervalo
    for (i=0; i<dimensao;i++){
        aux = (int) val[i] *k;
        intervalos[aux]++;
    }
    }

void imprime_histograma (int k, int interval[]){
    int i, j;
    int max_hist=0;
    //contagem de asteriscos para cada intervalo
    for (i=0;i<k;i++)
        printf("%d\n", interval[i]);
    //ver maximo do histograma
    for(i=0;i<k;i++){
        if (interval[i]>max_hist) {
            max_hist=interval[i];
        }
    }

    //para cada linha
    for(j= max_hist;j>0;j--){
        //para cada coluna
        for (i=0;i<k;i++){
            if(interval[i]>=j){
                printf("*");
            }else{
                printf(" ");
            }
        }
printf("\n");
    }
}

