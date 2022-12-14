#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, c, d, u;
    printf("Introduza o primeiro algarismo\n");
    scanf("%d", &c);
    printf("Introduza o segundo algarismo\n");
    scanf("%d", &d);
    printf("Introduza o terceiro algarismo\n");
    scanf("%d", &u);
    n= (c*100+d*10+u)*2;
    printf("O dobro do numero formado pelo algarismos e: %d. \n",n);
    return 0;
}
