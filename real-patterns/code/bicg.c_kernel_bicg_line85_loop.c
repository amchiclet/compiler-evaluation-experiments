#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  q[2100 + 0] ;
extern int j;
extern int m;
extern double  s[1900 + 0] ;
extern double  r[2100 + 0] ;
extern double  A[2100 + 0][1900 + 0] ;
extern double  p[1900 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        q[i] = 0.0;
        for(j = 0; j < m; j++)
        {
            s[j] = s[j] + r[i] * A[i][j];
            q[i] = q[i] + A[i][j] * p[j];
        }
    }

#pragma endscop
}
