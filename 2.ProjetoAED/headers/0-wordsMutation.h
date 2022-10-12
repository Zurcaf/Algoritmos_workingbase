#ifndef WORDSMUTATION_H
#define WORDSMUTATION_H

#define DICT_EXT ".dict"
#define PALS_EXT ".pals"
#define STATS_EXT ".stats"

void argsCheck(int argc);
void dictAndPalsCheck(char* argv[]);
void dictAndPalsAloc(char *argv[], char **dictLocation, char **palsLocation);
void fillPalsActivation(char *palsLocation, bool **palsActivation, int *maxLen);

#endif