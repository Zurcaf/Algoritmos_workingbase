#include <stdio.h>


// declaração da função
int max (int, int);

int main()
{
    int num1=0, num2;

    while (num1==0) {
        printf("Introduza um numero diferente de 0\n");
        scanf("%d", &num1);
    }

    printf("Introduza um numero\n");
    scanf("%d", &num2);

    int ret;
    ret=max(num1,num2);
    if (ret==0)
        printf ("Os numeros são iguais\n");
    else
        printf("O maximo entre os dois numero é %d\n", ret);

    return 0;
}

int max (int num1, int num2){
    if (num1<num2)
        return num2;
    else if (num2<num1)
        return num1;
    else return 0;

    }
