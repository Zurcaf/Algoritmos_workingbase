#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LINES 1000
	
int main(int argc, char** argv) {
	char namef[100]; int count = 0;
	FILE* fp = fopen(argv[1],"r");
	char** NameSet = NULL;
	while(fgets(namef,100,fp)) {
		if(NameSet == NULL)
			NameSet = (char **) malloc(sizeof(char*)*MAX_LINES);
		else {
			NameSet[count] = (char *) malloc(sizeof(char)*(strlen(namef)+1));
			strcpy(NameSet[count], namef);
			count++;
		}
	}
	fclose(fp);

	// just to test if it was read => not needed in the exam !
	int i = 0;
	for ( i = 0; i < count; i++ )
		printf("%s", NameSet[i]);
	// clean
	for ( i = 0; i < count; i++ )
		free(NameSet[i]);
	free(NameSet);
	return 0;
}
