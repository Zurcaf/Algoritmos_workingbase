#include <stdio.h>
#include <stdlib.h>

int main()
{
    int main()
{
    int i, primeira=1;
    double v0, radianos, angulo, dist_cesto, d, diametro, angulo_min, angulo_MAX;

    printf("DEFINA A DISTANCIA DO CESTO \nO DIAMETRO DO CESTO E \nA VELOCIDADE INICIAL\n");
    scanf("%lf %lf %lf", &dist_cesto, &diametro, &v0);

//SÓ ATÉ 45 PORQUE O ANGULO OS ANGULOS SAO SIMÉTRICOS PARA 45 ENTAO POSSO FAZER ATE 45 E METER TODOS OS ANGULOS ATÉ 45 E 90 MENOS ESSES ANGULOS
    i=0;
    while (i<=45/PRECISAO) {
        angulo=i*PRECISAO;
        radianos= (pi*angulo)/180;
        d= ((pow(v0, 2)) * (sin(2*radianos))) /g;

        if (d > dist_cesto-diametro/2 && d < dist_cesto+diametro/2) {
//CALCULAR O ANGULO MINIMO
            if(primeira==1) {
                primeira=0;
                angulo_min=angulo;
                    }
//CALCULAR O ANGULO MÁXIMO
            angulo_MAX= angulo;
            }
        i++;
    }
    if(primeira==1){
        printf("NAO EXISTE ANGULO POSSIVEL");
    }

    else{
        printf("\nA Gama de angulos vai de %.2lf graus a %.2lf graus e de %.2lf graus a %.2lf graus", angulo_min, angulo_MAX, 90-angulo_MAX, 90- angulo_min);
    }

    return 0;
}

}
