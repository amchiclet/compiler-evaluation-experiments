#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int i;
extern int  b[10][10] ;
extern int  a[10][10] ;

void loop()
{
#pragma scop

    for(j = 0; j < 10; j++) for(i = 0; i < 10; i++) b[j][i] =(a[i][j] + a[j][i]) / 2;

#pragma endscop
}
