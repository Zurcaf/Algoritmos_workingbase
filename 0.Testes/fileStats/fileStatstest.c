#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{

    // void getStats(char *locationStats, int *lenCount)
    char *locationStats;
    int *lenCount;


    FILE *palsPointer;
    char* word1, word2;
    int mode;


    // abrir o ficheiro e verificar se foi aberto com sucesso
    palsPointer = (FILE *)fopen(locationStats, "r");
    if (palsPointer == (FILE *)NULL)
    {
        fprintf(stderr, "File %s cannot be read.  Please correct.\n", locationStats);
        exit(0);
    }

    char word[40]; // buffer para a palavra

    // int i, j;

    // scan dos problemas
    while (fscanf(palsPointer, "%s %s %d", word1, word2, mode) == 1)
    {
        if (mode = 1)
        {
        binarySearch(tabs[strlen(word1)], word1, lenCount(strleng(word1));
        }
        else if (mode = 2)
        {
            
        }

      // fopen(locationStats=strcat(".pals.stats"));

    }

    return 0;
}

