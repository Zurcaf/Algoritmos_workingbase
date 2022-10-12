

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