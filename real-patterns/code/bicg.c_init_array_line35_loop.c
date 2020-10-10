#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  r[2100 + 0] ;
extern int j;
extern int m;
extern double  A[2100 + 0][1900 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        r[i] =((double )(i % n)) / n;
        for(j = 0; j < m; j++) A[i][j] =((double )(i *(j + 1) % n)) / n;
    }

#pragma endscop
}
