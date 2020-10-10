#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern double  corr[1200 + 0][1200 + 0] ;
extern int j;
extern int k;
extern int n;
extern double  data[1400 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m - 1; i++)
    {
        corr[i][i] = 1.0;
        for(j = i + 1; j < m; j++)
        {
            corr[i][j] = 0.0;
            for(k = 0; k < n; k++) corr[i][j] += data[k][i] * data[k][j];
            corr[j][i] = corr[i][j];
        }
    }

#pragma endscop
}
