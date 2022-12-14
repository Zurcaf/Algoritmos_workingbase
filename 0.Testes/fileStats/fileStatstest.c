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
    char *word1[WORD_LEN_MAX], word2;
    int mode;

    // abrir o ficheiro e verificar se foi aberto com sucesso
    palsPointer = (FILE *)fopen(locationPals, "r");
    if (palsPointer == (FILE *)NULL)
    {
        fprintf(stderr, "File %s cannot be read.  Please correct.\n", locationStats);
        exit(0);
    }

    char word[40]; // buffer para a palavra

    // scan dos problemas e escrita da resposta em . pals.stats
    while (fscanf(palsPointer, "%s %s %d", word1, word2, mode) == 1)
    {
        fopen(locationStats = strcat(".pals", ".stats")); // ISTO ESTA MAL

        if (mode = 2)
        {
        binarySearch(tabs[strlen(word1)], word1, lenCount(strleng(word1));
        if (result = -1)
        {
                fprintf("Word is not present in the dictionary", locationStats);
        }
        binarySearch(tabs[strlen(word1)], word2, lenCount(strleng(word2));
         if (result = -1)
        {
                fprintf("Word is not present in the dictionary", locationStats);
        }
        fprintf("%s %d \n %s %d", word1, \result of first bs\, word2, \result of second bs\, locationStats);
        }

        if (mode = 1)
        {
            fprintf("%d", lenCount[strlen(word1)], locationStats);
        }
    }

    fprintf(stderr, "File %s cannot be read.  Please correct.\n", locationStats);
    exit(0);

    return 0;
}
