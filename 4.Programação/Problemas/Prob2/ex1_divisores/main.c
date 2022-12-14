#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, num, soma=0;
    float val_med;

    printf("Escreva um numero natural: ");
    scanf("%d", &num);

    for (i= num; i!=0; i--){
        if((num%i)==0){
            printf("O numero %d é divisor de %d!\n", i, num);
            soma+=i;
        }
    }

    val_med=(soma/2);
    printf("O valor medio dos divisores é %.3f\n", val_med);

    return EXIT_SUCCESS;
}
