#include <stdio.h>
void fun(int *a, int *b) {
  static int count = 10;
  *a -= 2;
  *b = ++count;
}
int main() {
  int i = 0, j = 0;
  for ( i = 8; i > 0; i-- ) fun(&i, &j);
  printf("%d %d\n", i, j);
}