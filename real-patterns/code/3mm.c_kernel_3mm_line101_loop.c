#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ni;
extern int j;
extern int nl;
extern double  G[800 + 0][1100 + 0] ;
extern int k;
extern int nj;
extern double  E[800 + 0][900 + 0] ;
extern double  F[900 + 0][1100 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < ni; i++) for(j = 0; j < nl; j++)
        {
            G[i][j] = 0.0;
            for(k = 0; k < nj; ++k) G[i][j] += E[i][k] * F[k][j];
        }

#pragma endscop
}
