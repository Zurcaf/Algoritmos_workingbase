#ifndef WORDSMUTATION_H
#define WORDSMUTATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "1-dicionario.h"
#include "2-pals.h"
#include "3-fileStats.h"


#define DICT_EXT ".dict"
#define PALS_EXT ".pals"
#define STATS_EXT ".stats"
#define WORD_LEN_MAX 70
#define EXT_NAME_MAX 40
#define LINE_MAX 1000

void argsCheck(int argc);
void dictAndPalsCheck(char* argv[]);
void dictAndPalsAloc(char *argv[], char **dictLocation, char **palsLocation);
void fillReqPals(char *palsLocation, bool **palsActivation, int *maxLen);

#endif