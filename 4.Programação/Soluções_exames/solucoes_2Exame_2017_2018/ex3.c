#include <stdio.h>

int main(){
  int i=0, j=0, k, n, r;
  k = 2; n = 3; r = 4;
  for( j = k; j <= n; j++ ) {
    for( i = 1; i <= r; i++ ) {
      printf("%d ", i*j);
    }
    printf("\n");
  }
}
