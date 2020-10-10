#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ni;
extern int j;
extern int nl;
extern double  D[800 + 0][1200 + 0] ;
extern int nk;

void loop()
{
#pragma scop

    for(i = 0; i < ni; i++) for(j = 0; j < nl; j++) D[i][j] =((double )(i *(j + 2) % nk)) / nk;

#pragma endscop
}
