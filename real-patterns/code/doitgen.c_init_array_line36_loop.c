#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int np;
extern int j;
extern double  C4[160 + 0][160 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < np; i++) for(j = 0; j < np; j++) C4[i][j] =((double )(i * j % np)) / np;

#pragma endscop
}
