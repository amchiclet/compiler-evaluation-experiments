#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nk;
extern int j;
extern int nj;
extern double  B[1200 + 0][1100 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < nk; i++) for(j = 0; j < nj; j++) B[i][j] =((double )(i *(j + 2) % nj)) / nj;

#pragma endscop
}
