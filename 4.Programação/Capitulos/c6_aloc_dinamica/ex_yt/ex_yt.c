#include <stdio.h>
#include <stdlib.h>



int main ()
{
    int n;
    int i;
    
    printf("Enter size of array\n");
    scanf("%d", &n);

    int *A =(int*)malloc(sizeof(int)* n);
    
    // int A[n];

    for(i = 0; i<n; i++)
    {
        A[i]= i+1;
    }
    
    //free(A);

    for(i =0; i<n; i++)
    {
        // A[i]=i+1;
        printf("%d ", A[i]);
    }

    free(A);
}