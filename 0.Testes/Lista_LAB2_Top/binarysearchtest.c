// #include <stdio.h>

//  // Returns index of nome if it is present in tabs,
//     // else return -1



//     int binarySearch(char **tabs, char *nome, int n)
//     {
//         int l = 0 ;
//         int r = n - 1;
//         while (l <= r)
//         {
//             int m = l + (r - l) / 2;
 
//         int res = -10;   //

//         char nome= 0;
// int i = 0;
// for (i = 0; i < n; i++)
// {
//      if (nome == (tabs[m][i]))
//             res = 0;
             
 
//             // x é o elemento do meio? 
//             if (res == 0)
//                 return m;
 
//             // se x é maior do que elemento do meio, ignorar metade esquerda
//             if (nome > (tabs[m][i]))
//                 l = m + 1;
 
//             // se x é menor do que elemento do meio, ignorar metade direita
//             else
//                 r = m - 1;
//         }
 
//         return -1;
    
// }

       
//     }
 

//     int main()
//     {
//         char **tabs = { "cruz", "fred", "martins", "lazaro"};
//         char *nome = {"cruz"};
//         int n = 4;
//         int result = binarySearch(tabs, nome, n);
 
//         if (result == -1)
//             printf("Element not present");
//         else
//             printf("Element found at index %d", result);
//     }

#include <stdio.h>

#include <string.h>

int binarySearchString(char tabs[5][5], char *nome, int n)
{
    int lower = 0;
    int upper = n - 1;
    while (lower <= upper)
    {
        int mid = lower + (upper - lower) / 2;
        int res;
        if (strcmp(nome, (tabs[mid])) == 0 )
            res = 0;
        if (res == 0)
            return mid;
        if (strcmp(nome, (tabs[mid])) > 0 )
            lower = mid + 1;
        else
            upper = mid - 1;
    }
    return -1;
}


int main()
{
    char tabs[5][5];
    strcpy(tabs[0], "cruz");
    strcpy(tabs[1], "fred");
    strcpy(tabs[2], "mart");
    strcpy(tabs[3], "laza");
    strcpy(tabs[4], "epif");

    char *nome = tabs[2];
    int n = 4;
    int result = binarySearchString(tabs, nome, n);
    if (result == -1)
        printf("Element not present");
    else
        printf("Element found at index %d", result);
}