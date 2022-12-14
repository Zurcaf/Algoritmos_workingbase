/******************************************************************************
 * (c) 2010-2020 IST AED Team
 * Last modified: abl 2020-04-21
 *
 * NAME
 *   sortwords.c
 *
 * DESCRIPTION
 *   Main program for unique word finding and sorting with tables
 *
 * COMMENTS
 *   Code for preliminary distribution, to be completed
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "word.h"

enum sort_order {ascending, descending};

enum sort_criteria {alphabetic, length, occurrences};

int OP_CNT = 0; /* global variable, to simplify complexity assessment */

void swap(Item *a, Item *b)
{
   Item tmp = *a;
   *a = *b;
   *b = tmp;
   OP_CNT += 4;
}

int partition(Item *a, int l, int r, int (*less)(Item, Item))
{
   int i = l - 1, j = r;
   Item v = a[r];
   OP_CNT++;
   for (;;)
   {
      while (less(a[++i], v))
      {
         OP_CNT++;
      };
      while (less(v, a[--j]))
      {
         OP_CNT++;
         if (j == l)
            break;
      };
      if (i >= j)

         break;
      swap(&a[i], &a[j]);
      OP_CNT+=2;
   }
   OP_CNT+=2;
   swap(&a[i], &a[r]);
   return i;
}

/*qsort para ordenar arr*/
void quickSort(Item arr[], int l, int r, int (*less) (Item, Item))
{
   int i;
   if (r <= l)
      return;
   i = partition(arr, l, r, less);
   quickSort(arr, l, i-1, less);
   quickSort(arr, i+1, r, less);
}


/******************************************************************************
* main ()
*
*****************************************************************************/

int main(int argc, char **argv)
{
   int TnumWords;              /* total number of words in input file */
   int numWords;               /* number of distint words in input file */
   WordTab wordtab;              /* table holding the structure */

   /* default initialization for alfabetic order and ascending */
   enum sort_criteria criterio = alphabetic;
   enum sort_order sentido  = ascending;
   char *file = argv[1];

   argv++;             /* get past prog and file names */
   while (*(++argv)) {
      if (strcmp(*argv, "-alfabetica") == 0)
         criterio = alphabetic;
      else if (strcmp(*argv, "-ocorrencias") == 0)
         criterio = occurrences;
      else if (strcmp(*argv, "-comprimento") == 0)
         criterio = length;
      else if (strcmp(*argv, "-a") == 0)
         sentido = ascending;
      else if (strcmp(*argv, "-d") == 0)
         sentido = descending;
      else {
         fprintf(stderr, "Wrong arguments\n");
         exit(3);
      }
   }
   TnumWords = AllocWordArray(&wordtab, file);
   printf("Total number of words: %d\n", TnumWords);

   numWords = FillInWordArray(wordtab, file);
   printf("Number of different words = %d\n", numWords);

   OP_CNT = 0;

   /*  Call the sorting function using as argument the
       appropriate comparison function selected by user option */

   if ((criterio == alphabetic) && (sentido == ascending)) {
      quickSort(wordtab, 0, numWords-1, LessAlphabetic);
   }

   if((criterio == alphabetic) && (sentido == descending)) {
      quickSort(wordtab, 0, numWords-1, GreaterAlphabetic);
   }

   if((criterio == length) && (sentido == ascending)) {
      quickSort(wordtab, 0, numWords-1, LessLength);
   }

   if((criterio == length) && (sentido == descending)) {
      quickSort(wordtab, 0, numWords-1, GreaterLength);
   }

   if((criterio == occurrences) && (sentido == ascending)) {
      quickSort(wordtab, 0, numWords-1, LessOccurrences);
   }

   if((criterio == occurrences) && (sentido == descending)) {
      quickSort(wordtab, 0, numWords-1, GreaterOccurrences);
   }
   /* other user options */
   /*==== TODO ====*/

   /* ---------------------------------------- */
   printf("Accesses count for sort: %d\n", OP_CNT);

   WriteFile(wordtab, file, numWords);
   /*  printf("Number of different words: %d\n", n_palavras);  */

   /* -- Insert code to call functions to free allocated memory -- */

   FreeWordArray(&wordtab, numWords);

   /*==== TODO ====*/

   /* ------------------------------------------------------------ */

   return 0;
}
