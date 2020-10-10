#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nj;
extern int j;
extern int nl;
extern double  C[900 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < nj; i++) for(j = 0; j < nl; j++) C[i][j] =((double )(i *(j + 3) % nl)) / nl;

#pragma endscop
}
