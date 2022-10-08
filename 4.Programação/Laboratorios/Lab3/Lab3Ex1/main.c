#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_GERA 2
#define MIN 1
#define MAX 10
int main()
{
    int a, b, s, n;
    n=1;
    srand(time(NULL));
    a=(rand()% (MAX-MIN+1))+MIN;
    b=(rand()% (MAX-MIN+1))+MIN;

    while (n==1){
    printf("Indica o resultado de: %d*%d=", a,b);
    scanf("%d", &s);

    if (s==a*b)
        {printf("A resposta esta correta %d*%d e %d \n",a,b,s);
         n=0;
        }
    else
        {printf("%d nao e a resposta correta. \n", s);
         printf("Deseja tentar de novo? (0->nao 1->sim) \n");
         scanf("%d", &n);
        }
    }
   return 0;
}

