#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int main(){

   FILE *fp1;

   fp1 = fopen("./test.txt", "w+");
   fprintf(fp1, "22 . . . 3 . . . 2\n");
   fputs("This is testing for fputs...\n", fp1);
   fclose(fp1);


   FILE *fp2;
   char buff[255];

   fp2 = fopen("./test.txt", "r");

   while (buff != "\n")
   {
       fscanf(fp2, "%s", buff);
       printf("1 : %s\n", buff);
   }

   fgets(buff, 255, (FILE*)fp2);
   printf("2: %s\n", buff );
  
   fclose(fp2);


    char delimitador[]= " ";
int i=0;
int w=0;
char string[]= "   ola este é o meu teste                               ptsssss";
char *apontador = strtok(string, delimitador);

apontador = strtok(NULL, delimitador);
apontador = strtok(NULL, delimitador);
char *strarr[200];

// for (i=0; apontador != NULL; i++){
//     // // strarr[w++] = strptr;
//     // strptr = strtok(NULL, delimitador);
        
//     // printf("Posicao geral:%s\nPosicao Escalao:%s\n", strarr[0], strarr[0]);
//     // w++;
//     // for (int r=0; r<8; r++){
//     //     printf ("%s ", strarr[0]);
//     //}
// }
}


// teste 1 a funcionar

// int main(){
//     char delimitador[]= " ";
// int i;
// char strwork[]= "   ola este é o meu teste                               ptsssss";
// char *strptr = strtok(strwork, delimitador);
// char *strarr[7];

//     while (strptr != NULL)
//         {
//         strarr[i++] = strptr;
//         strptr = strtok(NULL, delimitador);
//         }
//     printf("Posicao geral:%s\nPosicao Escalao:%s\n", strarr[0], strarr[2]);
//     for (i=0; i<7; i++){
//         printf ("%s ", strarr[i]);
//     }
// }