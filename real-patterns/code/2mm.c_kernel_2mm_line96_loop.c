#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ni;
extern int j;
extern int nl;
extern double  D[800 + 0][1200 + 0] ;
extern double beta;
extern int k;
extern int nj;
extern double  tmp[800 + 0][900 + 0] ;
extern double  C[900 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < ni; i++) for(j = 0; j < nl; j++)
        {
            D[i][j] *= beta;
            for(k = 0; k < nj; ++k) D[i][j] += tmp[i][k] * C[k][j];
        }

#pragma endscop
}
