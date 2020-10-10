#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern int m;
extern float ** restrict data;
extern float * restrict mean;
extern float x;
extern float * restrict stddev;

void loop()
{
#pragma scop

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= m; j++)
        {
            data[i][j] -= mean[j];
            x =(sqrt(((float )n)));
            x *= stddev[j];
            data[i][j] /= x;
        }
    }

#pragma endscop
}
