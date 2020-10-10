#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long jt;
extern long n;
extern int tile_size;
extern long it;
extern long j;
extern long i;
extern long jj;
extern double * restrict out;
extern double  weight[4 + 1][4 + 1] ;
extern double * restrict in;
extern long ii;

void loop()
{
#pragma scop

    for(jt = 2; jt < n - 2; jt += tile_size)
    {
        for(it = 2; it < n - 2; it += tile_size)
        {
            for(j = jt; j <((n - 2 < jt + tile_size?n - 2 : jt + tile_size)); j++)
            {
                for(i = it; i <((n - 2 < it + tile_size?n - 2 : it + tile_size)); i++)
                {
                    for(jj =(- 2); jj <= 2; jj++) out[i + j * n] += weight[0 + 2][jj + 2] * in[i +(j + jj) * n];
                    for(ii =(- 2); ii < 0; ii++) out[i + j * n] += weight[ii + 2][0 + 2] * in[i + ii + j * n];
                    for(ii = 1; ii <= 2; ii++) out[i + j * n] += weight[ii + 2][0 + 2] * in[i + ii + j * n];
                }
            }
        }
    }

#pragma endscop
}
