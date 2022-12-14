#include <stdio.h>

void bs(int a[], int l, int r) {
	int i, j, t;
	for (i = l; i < r; i++)
		for (j = r; j > i; j--)
			if (a[j] < a[j-1]) {
				t = a[j-1]; 
				a[j-1]=a[j]; 
				a[j]=t;
			}
}

int main(int argc, char** argv) 
{
	int i = 0;
	int arr[] = {24,-1,1,37,16,47,22,7,10,15};
	bs(arr, 0, 7);
	for ( i = 0; i < 10; i++ ) printf("%d\n", arr[i]);
}