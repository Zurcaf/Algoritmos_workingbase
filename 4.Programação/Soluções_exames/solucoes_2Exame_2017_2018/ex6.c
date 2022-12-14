#include <stdio.h>
#include <stdlib.h>
void populate(char *parray){
    parray = (char*)malloc(2*sizeof(char));
    parray[0] = 'A';
    *(parray+1) = 'X';
}
int main(){
    char string[] = "EXAM";
    char *p1 = NULL; char *p2[2]; 
    p2[0] = &(string[0]);
    p2[1] = p2[0]+2;
    p1 = p2[1] - 1;
    populate(p1);
    printf("%c %c %c\n", p1[0], **(p2 + 1), *p2[0] );
}

