#include "0Main.h"

// void getStats(char *locationStat, int *lenCount)
void getStats(char **locationStats, int *lenCount, char ***tabs, char *locationPals, int lenMax)
{
    FILE *palsPointer = NULL, *statsPointer=NULL;
    char word1[WORD_LEN_MAX], word2[WORD_LEN_MAX]; // buffer para a palavra
    int mode=0, bsResult1=-2, bsResult2=-2;

    for(int i=0; i<WORD_LEN_MAX; i++)
    {
        word1[i] = '\0';
        word2[i] = '\0';
    }
    // abrir o ficheiro e verificar se foi aberto com sucesso
    palsPointer = (FILE *)fopen(locationPals, "r");
    if (palsPointer == (FILE *)NULL)
    {
        fprintf(stderr, "File %s cannot be read.  Please correct.\n", locationPals);
        exit(0);
    }

    (*locationStats) = (char*)calloc(((strlen(locationPals)-(strlen(PALS_EXT))) + (strlen(STATS_EXT)) + 1), sizeof(char));
    if ((*locationStats) == NULL)
    {
        fprintf(stderr, "ERROR: not enough memory available!\n");
        exit(4);
    }
    cutPals(&locationPals);
    strcpy((*locationStats), locationPals);
    strcat((*locationStats), STATS_EXT);

    statsPointer = (FILE *)fopen((*locationStats), "w");
    if (statsPointer == (FILE *)NULL)
    {
        fprintf(stderr, "File %s cannot be created.  Please correct.\n", (*locationStats));
        exit(0);
    }

    // scan dos problemas e escrita da resposta em . pals.stats
    while (fscanf(palsPointer, "%s %s %d", word1, word2, &mode) == 3)
    {
        if(strlen(word1)!=strlen(word2) || strlen(word1) > (lenMax) || strlen(word2) > (lenMax))
            {
                fprintf(statsPointer, "%s %s %d \n \n", word1, word2, mode);
                continue;
            }


        bsResult1 = binarySearch(tabs[strlen(word1)], word1, lenCount[strlen(word1)]);
        bsResult2 = binarySearch(tabs[strlen(word2)], word2, lenCount[strlen(word2)]);

        if (bsResult1 == -1 || bsResult2 == -1)
        {
            fprintf(statsPointer, "%s %s %d \n \n", word1, word2, mode);
            continue;
        }   

        switch (mode)
        {
        case 1:
                fprintf(statsPointer, "%s %d\n\n", word1, lenCount[strlen(word1)]);
        break;
        case 2:
            fprintf(statsPointer, "%s %d \n%s %d \n\n", word1, bsResult1, word2, bsResult2);
        break;
        default:
            fprintf(statsPointer, "%s %s %d\n\n", word1, word2, mode);
            break;
        }
    }
    fclose(statsPointer);
    fclose(palsPointer);
}


int binarySearch(char **tabs, char *nome, int n)
{
    int lower = 0;
    int upper = n - 1;
    int mid = lower + (upper - lower) / 2;
    int res =1;
    while (lower <= upper)
    {
        mid = lower + (upper - lower) / 2;
        if (strcmp(nome, (tabs[mid])) == 0)
            res = 0;
        if (res == 0)
            return mid;
        if (strcmp(nome, (tabs[mid])) > 0)
            lower = mid + 1;
        else
            upper = mid - 1;
    }
    return -1;
}
void cutPals(char **locationPals)
{
    (*locationPals)[(strlen(*locationPals) - strlen(PALS_EXT))] = '\0';
}
