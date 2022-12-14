#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n[3], r[3], d[3], y;
    printf("Introduza o primeiro tempo (h:min:seg)\n");
    scanf("%d:%d:%d", &n[0],&n[1],&n[2]);
    printf("Introduza o segundo tempo menor que o primeiro (h:min:seg)\n");
    scanf("%d:%d:%d", &r[0],&r[1],&r[2]);
    y=(n[0]*3600 + n[1]*60 + n[2])-(r[0]*3600 + r[1]*60 + r[2]);
    d[0]=y/3600;
    d[1]=(y%3600)/60;
    d[2]=(y%3600)%60;
    printf("%d:%d:%d", d[0],d[1],d[2]);
    return 0;
}
