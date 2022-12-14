#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int main(){
    char string1[3] = "$\n";
    printf("%s", string1);

    if (string1[1] == '\n') string1[1]= ' ';
    printf("%s", string1);

}