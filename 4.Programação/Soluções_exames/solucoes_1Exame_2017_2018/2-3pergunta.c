#include <stdio.h>

#define FOO(x) (2*x-x)

int main() 
{
	int x = 6;
	int y = 19;
	int z = 21;

	while(--y > z-x) {
		x--;
		z += 2;
	}
	printf("%d %d\n",y,z);

    int val = 10;
    printf("%d\n", FOO(val+5));
}
