#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, a;
    printf("Insira o numero do mes pretendido\n");
    scanf("%d", &m);
    switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        printf("O mes tem 31 dias. \n");
        break;
        case 4:
        case 6:
        case 9:
        case 11:
        printf("O mes tem 30 dias. \n");
        break;
        case 2:
            printf("Diga se o ano é: \n 1.Comum \n 2.bissexto\n");
            scanf("%d", &a);
            switch (a) {
                case 1:
                printf("O mes tem 28 dias.");
                break;
                case 2:
                printf("O mes tem 29 dias.");
                break;
                default:
                printf("Opcao invalida.");
               }
        break;
            default:
            printf("Opcao invalida.");
    }
    return 0;
}
