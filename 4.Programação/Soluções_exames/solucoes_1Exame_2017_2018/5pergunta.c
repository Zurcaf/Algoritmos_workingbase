#include <stdio.h>

void compute(int v[], int n, int *r) {
	int *p = v;
	int *u = v + n - 1;
	*r = 0;
	while (n > 0) {
		if (*p > *u) {
			++*r;
			*u = *p;
		}
		++p; --u; --n;
	}
}
int main() {
	int v[] = {3, 5, 7, 0, 9, 15, 12, 13, 7};
	int x = 0; int y = 9;
	compute(v, y, &x);
	printf("%d %d\n", x, y); return 0;
}
