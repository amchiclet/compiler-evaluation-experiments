#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ni;
extern int j;
extern int nk;
extern double  A[1000 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < ni; i++) for(j = 0; j < nk; j++) A[i][j] =((double )(i *(j + 1) % nk)) / nk;

#pragma endscop
}
