#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define g 9.8
#define pi 3.14159

int main()
{
    int b=0;
    float d, v, c, td, ar, a=0;
    printf("Introduza um valor para a distancia ao cesto: ");
    scanf("%f",&d);
    printf("Introduza um valor para a velocidade inicial: ");
    scanf("%f",&v);
    printf("Introduza um valor para o diametro do cesto: ");
    scanf("%f",&c);
    while (a < 90)
  {
            ar = ((a*pi)/180); //conversão para radianos
            td =(v*v*(sin(2*ar)/g));

      if (( td<=(d+(c/2))) && (td>=(d-(c/2))))
      {
          printf ("Um angulo aceitável e %.2f graus.\n", a);
          b=1;
      }
      a+=0.1;

    }
    if (b==0)
     printf("Nao há angulos possiveis.");

    return 0;
}
