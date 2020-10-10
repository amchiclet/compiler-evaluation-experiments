#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ni;
extern int j;
extern int nj;
extern double  tmp[800 + 0][900 + 0] ;
extern int k;
extern int nk;
extern double alpha;
extern double  A[800 + 0][1100 + 0] ;
extern double  B[1100 + 0][900 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < ni; i++) for(j = 0; j < nj; j++)
        {
            tmp[i][j] = 0.0;
            for(k = 0; k < nk; ++k) tmp[i][j] += alpha * A[i][k] * B[k][j];
        }

#pragma endscop
}
