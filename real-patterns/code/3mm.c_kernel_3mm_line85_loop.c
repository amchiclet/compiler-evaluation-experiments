#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ni;
extern int j;
extern int nj;
extern double  E[800 + 0][900 + 0] ;
extern int k;
extern int nk;
extern double  A[800 + 0][1000 + 0] ;
extern double  B[1000 + 0][900 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < ni; i++) for(j = 0; j < nj; j++)
        {
            E[i][j] = 0.0;
            for(k = 0; k < nk; ++k) E[i][j] += A[i][k] * B[k][j];
        }

#pragma endscop
}
