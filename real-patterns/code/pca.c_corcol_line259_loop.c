#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int m;
extern float * restrict mean;
extern int i;
extern int n;
extern float ** restrict data;

void loop()
{
#pragma scop

    for(j = 1; j <= m; j++)
    {
        mean[j] = 0.0;
        for(i = 1; i <= n; i++)
        {
            mean[j] += data[i][j];
        }
        mean[j] /=((float )n);
    }

#pragma endscop
}
