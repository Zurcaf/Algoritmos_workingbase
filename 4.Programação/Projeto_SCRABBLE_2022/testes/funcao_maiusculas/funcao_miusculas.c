#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// int main(){
//     char string;
//     char STR;

//     scanf("%c", &string);
//     printf("Antes de topper %c\n", string);
//     STR = toupper(string);
//     string = STR;
//     printf("Depois %c\n", string);
// }

int main(){
    char string;
    char STR;

    scanf("%c", &string);
    printf("Antes de topper %c\n", string);
    STR = tolower(string);
    string = STR;
    printf("Depois %c\n", string);
}