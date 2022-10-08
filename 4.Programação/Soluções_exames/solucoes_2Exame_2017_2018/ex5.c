#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
  //definitions
	int i = 3, k[]={2,4,6,8,10,12}, *x=&i, *y=k;
	double d=1.5;
	struct point {
    int x;
    int y;
	  char *name;
  } pt[] = {{200,40,"begin"},{300,100,"end"}}, *pp = pt;
  // expressions
  printf("%d\n", (++pp)->x);
  pp--;
  printf("%d\n", pt[1].x*i/5);
  printf("%d\n", k[i++]);
  i--;
  printf("%lf\n", i+k[++i]+d);
  i--;
//printf("%d\n", pt[i--].y+50); // not valid
//printf("%d", pt[0]->name[0]); // not valid
  printf("%s\n", (*pp).name + 2);
  printf("%d\n", strcmp((*pp).name, "begin"));
  return EXIT_SUCCESS;
}
