#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    int n,i;
    double num, num1;
    printf("Insira um numero real positivo\n");
    scanf("%1f", &num);
    printf("indique o numero, entre 1 e 7 de casas decimais que pretende arredondar.\n");
    scanf("%d", &n);
    //for (i=0;i<n;++i) {

    num+=0.5;
    num1=(int)num;
    for(i=0;i<n;++i) {
        num1/=10.0;
    }
    printf ("o numero com arredondamento é: %f.\n", num1);
    return 0;
}
