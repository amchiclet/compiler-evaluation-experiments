#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern int m;
extern float * restrict interm;
extern float ** restrict data;
extern int k;
extern int k2;
extern float ** restrict symmat;

void loop()
{
#pragma scop

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= m; j++)
        {
            interm[j] = data[i][j];
        }
        for(k = 1; k <= 3; k++)
        {
            data[i][k] = 0.0;
            for(k2 = 1; k2 <= m; k2++)
            {
                data[i][k] += interm[k2] * symmat[k2][m - k + 1];
            }
        }
    }

#pragma endscop
}
