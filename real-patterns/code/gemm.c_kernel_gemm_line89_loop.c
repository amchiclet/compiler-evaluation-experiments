#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ni;
extern int j;
extern int nj;
extern double  C[1000 + 0][1100 + 0] ;
extern double beta;
extern int k;
extern int nk;
extern double alpha;
extern double  A[1000 + 0][1200 + 0] ;
extern double  B[1200 + 0][1100 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < ni; i++)
    {
        for(j = 0; j < nj; j++) C[i][j] *= beta;
        for(k = 0; k < nk; k++)
        {
            for(j = 0; j < nj; j++) C[i][j] += alpha * A[i][k] * B[k][j];
        }
    }

#pragma endscop
}
