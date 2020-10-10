#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long j;
extern long n;
extern long i;
extern long jj;
extern double * restrict out;
extern double  weight[4 + 1][4 + 1] ;
extern double * restrict in;
extern long ii;

void loop()
{
#pragma scop

    for(j = 2; j < n - 2; j++)
    {
        for(i = 2; i < n - 2; i++)
        {
            for(jj =(- 2); jj <= 2; jj++) out[i + j * n] += weight[0 + 2][jj + 2] * in[i +(j + jj) * n];
            for(ii =(- 2); ii < 0; ii++) out[i + j * n] += weight[ii + 2][0 + 2] * in[i + ii + j * n];
            for(ii = 1; ii <= 2; ii++) out[i + j * n] += weight[ii + 2][0 + 2] * in[i + ii + j * n];
        }
    }

#pragma endscop
}
