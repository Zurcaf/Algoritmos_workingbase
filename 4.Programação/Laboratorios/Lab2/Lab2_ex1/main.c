#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, h, m, s;
    printf("Introduza um numero inteiro de segundos\n");
    scanf("%d", &n);
    h=n/3600;
    m=(n%3600)/60;
    s=(n%3600)%60;
    printf("%dh %dmin %dseg", h, m, s);
    return 0;
}
