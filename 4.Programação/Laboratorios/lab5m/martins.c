#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int catsearch(char *string, char *s);
void ordfunc(char **linhas, char **linha_ord);

int main(int argc, char *argv[])
{
    FILE *ptr = fopen("RunResults.txt", "r");
    FILE *fileord;
    char str[100];
    int i = 0;
    char **linhas = (char **)malloc(140 * sizeof(char *));
    if (linhas == NULL)
    printf ("IMpossivel alocar memoria para linhas");
    char *linha_ord[140];

    while (fgets(str, 100, ptr))
    {
        *(linhas +i)  = malloc((strlen(str)+1) * sizeof(char));
        // if (linhas [])
        strcpy(linhas[i], str);
        i++;
    }
    fclose(ptr);

    if (argc == 1)
    {
        ordfunc(linhas, linha_ord);
        fileord = fopen("RunResults_out.txt", "w");
        for (i = 0; i < 140; i++)
        {
            fprintf(fileord, "%s", linha_ord[i]);
        }
        fclose(fileord);
    }
    else
    {
        char strinput[100];
        for (i = 1; i <= argc; i++)
        {
            strcpy(strinput, argv[i]);
            char strwork[100];
            for (i = 0; i < 139; i++)
            {
                if (strstr(linhas[i], strinput) != NULL)
                {
                    strcpy(strwork, linhas[i]);
                }
            }

            i = 0;
            char delim[] = "\t";
            char *strptr = strtok(strwork, delim);
            char *strarr[7];

            while (strptr != NULL)
            {
                strarr[i++] = strptr;
                strptr = strtok(NULL, delim);
            }
            printf("Posicao geral:%s\nPosicao Escalao:%s\n", strarr[0], strarr[2]);
        }
    }

    for (i = 0; i < 141; i++)
    {
        free(linhas[i]);
    }
    free(linhas);

    return 0;
}

void ordfunc(char **linhas, char **linha_ord)
{
    int j = 0, i = 0;
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "F20") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "F40") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "F45") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "M20") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "M35") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "M40") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "M45") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "M50") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "M55") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
    for (i = 0; i < 141; i++)
    {
        if (catsearch(linhas[i], "M60") == 0)
        {
            linha_ord[j] = linhas[i];
            j++;
        }
    }
}

int catsearch(char *string, char *s)
{
    if (strstr(string, s) == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}