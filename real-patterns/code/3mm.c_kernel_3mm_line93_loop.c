#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nj;
extern int j;
extern int nl;
extern double  F[900 + 0][1100 + 0] ;
extern int k;
extern int nm;
extern double  C[900 + 0][1200 + 0] ;
extern double  D[1200 + 0][1100 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < nj; i++) for(j = 0; j < nl; j++)
        {
            F[i][j] = 0.0;
            for(k = 0; k < nm; ++k) F[i][j] += C[i][k] * D[k][j];
        }

#pragma endscop
}
