
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) 
{ 

// fazer o casting do void pointer para o tipo de variavél dos elementos do vector.
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;

    return strcmp(*str_a, *str_b); // r=0 se forem iguais. r<0 -> 'a' deve estar antes do 'b'. r>0 -> 'a' deve estar depois de 'b'.
} 

int main ()
{

//dados de teste
    int i = 0, numbers = 5;
    char* array[] = {"cruz", "martins", "fred", "goncalo", "epifanio"};

// chamar qsort (lib function)
    qsort (array, numbers, sizeof(char*), compare);

// imprimir vector ordenado, (elemento a elemento)    
    for (i=0; i < numbers; i++)
         printf ("%s \n", array[i]);          
    return 0;
}