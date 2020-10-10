#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int m;
extern double  mean[1200 + 0] ;
extern int i;
extern int n;
extern double  data[1400 + 0][1200 + 0] ;
extern double float_n;

void loop()
{
#pragma scop

    for(j = 0; j < m; j++)
    {
        mean[j] = 0.0;
        for(i = 0; i < n; i++) mean[j] += data[i][j];
        mean[j] /= float_n;
    }

#pragma endscop
}
