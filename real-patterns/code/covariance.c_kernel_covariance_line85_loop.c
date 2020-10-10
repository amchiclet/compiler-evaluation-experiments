#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern double  cov[1200 + 0][1200 + 0] ;
extern int k;
extern int n;
extern double  data[1400 + 0][1200 + 0] ;
extern double float_n;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) for(j = i; j < m; j++)
        {
            cov[i][j] = 0.0;
            for(k = 0; k < n; k++) cov[i][j] += data[k][i] * data[k][j];
            cov[i][j] /= float_n - 1.0;
            cov[j][i] = cov[i][j];
        }

#pragma endscop
}
