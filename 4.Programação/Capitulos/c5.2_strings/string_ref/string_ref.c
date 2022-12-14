#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_string(char * str)
{
    strcpy(str, "test");
}

int main(int argc, char *argv[])
{
    char s[50]; 
    get_string(s);
    //s[0]='p';

    printf("%s\n", s);
    return 0;
}

//outra maneira de fazer igualmente boa

// void get_string(char * str, char str2)
// {
//     strcpy(str, str2);
// }

// int main(int argc, char *argv[])
// {
//     char s[50]; 
//     get_string(s, "test");
//     // s[0]='p';

//     printf("%s\n", s);
//     return 0;
// }


// da return da string mas não é o ideal

//     char * get_string()
// {
//     return "test";
// }

// int main(int argc, char *argv[])
// {
//     char *s = get_string();

//     printf("%s\n", s);
//     return 0;
// }