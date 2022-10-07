#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define rw (3*pow(10,9))
#define mw (3*pow(10,12))
#define inf (4.3*pow(10,14))
#define vl (7.5*pow(10,14))
#define uvl (3*pow(10,17))
#define xray (3*pow(10,19))

int main()
{
    float base, exp, freq;
    printf("Insira uma frequencia (base/expoente): \n");
    scanf("%f/%f", &base, &exp);
    freq= (base*(pow(10,exp)));

    if (freq<= rw)
        printf("A frequencia e de uma onda radio.");
    if ((freq<=mw) && (freq<mw))
        printf("A frequencia e de uma micro onda.");
    if ((freq<=inf) &&(freq<inf))
        printf("A frequencia e de uma luz infravermelha.");
    if ((freq >= inf) && (freq < vl))
        printf("A frequencia e de uma luz visivel.");
    if ((freq >= vl) && (freq < uvl))
        printf("A frequencia e de uma luz ultravioleta.");
    if ((freq >= uvl) && (freq < xray))
        printf("A frequencia e de um raio X.");
    if (freq >= xray)
        printf("A frequencia e de um raio gama.");

    return 0;
}
