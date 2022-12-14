#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char **strings;
    int total = 0;

    printf("numero de string: ");
    scanf("%d", &total);

    strings = malloc (total*sizeof(char*));
    
}

