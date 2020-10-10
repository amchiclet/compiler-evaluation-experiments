#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  e[1 << 6][1 << 6] ;
extern int k;
extern double  basis[1 << 2 + 5 - 1][1 << 2 + 5 - 1] ;
extern double  tbasis[1 << 2 + 5 - 1][1 << 2 + 5 - 1] ;
extern double  AUTOCORR[127] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            e[i][j] = 0;
            for(k = 0; k < n; k++)
            {
                e[i][j] +=(basis[i][k] - tbasis[i][k]) * AUTOCORR[k - j + 63];
            }
        }
    }

#pragma endscop
}
