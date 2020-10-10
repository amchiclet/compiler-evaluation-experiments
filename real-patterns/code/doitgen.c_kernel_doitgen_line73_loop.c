#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int r;
extern int nr;
extern int q;
extern int nq;
extern int p;
extern int np;
extern double  sum[160 + 0] ;
extern int s;
extern double  A[150 + 0][140 + 0][160 + 0] ;
extern double  C4[160 + 0][160 + 0] ;

void loop()
{
#pragma scop

    for(r = 0; r < nr; r++) for(q = 0; q < nq; q++)
        {
            for(p = 0; p < np; p++)
            {
                sum[p] = 0.0;
                for(s = 0; s < np; s++) sum[p] += A[r][q][s] * C4[s][p];
            }
            for(p = 0; p < np; p++) A[r][q][p] = sum[p];
        }

#pragma endscop
}
