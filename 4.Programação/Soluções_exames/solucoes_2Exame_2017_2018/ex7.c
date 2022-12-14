#include <stdio.h>
#include <stdlib.h>

void printNumber(unsigned int n){
  int pow = 1;

  while (pow * 10 <= n)
    pow *= 10;

  while ( n > 0 ){ // or pow != 0
    int d = n / pow;
    putchar((char)((int)'0' + d));
    n = n - pow*d;
    pow /= 10;
  }
}

int main()
{
    unsigned int a = 21435;
    printNumber(a);
    putchar('\n');
}

