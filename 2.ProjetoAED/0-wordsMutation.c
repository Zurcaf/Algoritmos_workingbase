#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/0-wordsMutation.h"
#include "headers/1-dicionario.h"
#include "headers/2-pals.h"

int main(int argc, char* argv[])
{
argsCheck(argc);

char* dictLocation;
char* palsLocation;

dictAndPalsCheck(argv, dictLocation, palsLocation);
saveDictionary(dictLocation);
savePals(palsLocation);




return 0;
}

void argsCheck(int argc)
{
    if (argc != 3)
    {
        fprintf(stderr, "ERROR: wrong number of arguments!\n");
        exit(1);
    }
}

void dictAndPalsCheck(char* argv[], char* dictLocation, char* palsLocation)
{

}