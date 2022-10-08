#include <stdio.h>

int main(){
    int dias, flag, num_mes, num_dias;
    
    do {
    printf("Que mês do ano quer saber o numero de dias?\n");
    scanf("%d", &num_mes);
    
    switch (num_mes){
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        num_dias=31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        num_dias=30;
        break;    
    case 2:
        num_dias=29;
        break;
    default: flag=1;
        break;
    }
    if (flag!=1){
    printf("O mês %d tem %d dias.\n", num_mes, num_dias);
    }else printf ("Programa Terminado\n");
    }while (flag!=1);
    return 0;
}