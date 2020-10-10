#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int k;
extern int j;
extern int m;
extern double ** restrict c;
extern int * restrict counts;
extern double ** restrict c1;

void loop()
{
#pragma scop

    for(i = 0; i < k; i++)
    {
        for(j = 0; j < m; j++)
        {
            c[i][j] =(counts[i]?c1[i][j] / counts[i] : c1[i][j]);
        }
    }

#pragma endscop
}
