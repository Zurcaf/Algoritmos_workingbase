#include <stdio.h>

struct {
    // char  c[8];
    int i[2];
    double d;
}teste;

int main ()
{
    printf ("%lu", sizeof(teste));
}