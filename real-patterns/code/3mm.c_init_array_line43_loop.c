#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nm;
extern int j;
extern int nl;
extern double  D[1200 + 0][1100 + 0] ;
extern int nk;

void loop()
{
#pragma scop

    for(i = 0; i < nm; i++) for(j = 0; j < nl; j++) D[i][j] =((double )(i *(j + 2) % nk)) /(5 * nk);

#pragma endscop
}
