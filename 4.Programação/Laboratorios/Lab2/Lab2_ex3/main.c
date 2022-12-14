#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define g (9.8)
#define pi (3.14159)
int main()
{
    float graus, rad, v, h_t;
    double d, h;
    printf("Insira o angulo de lançamento\n");
    scanf("%f", &graus);
    printf("Insira a velocidade de lancamento\n");
    scanf("%f", &v);
    printf("Insira a altura do tecto\n");
    scanf("%f", &h_t);
    rad=(2*pi*graus)/360;
    d=((pow(v,2))*sin(2*rad))/g;
    h=((pow(v,2))*pow(sin(rad),2)/(2*g));
    if (h_t<=h)
        printf("o projectil bate no tecto.");
        else{
        printf("o projectil nao bate no tecto\n");
        printf("O centro do cesto deve estar a %f metros do local de lancamento.", d);
        }
    return 0;
}
