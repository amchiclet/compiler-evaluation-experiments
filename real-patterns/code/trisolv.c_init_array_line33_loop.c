#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  x[2000 + 0] ;
extern double  b[2000 + 0] ;
extern int j;
extern double  L[2000 + 0][2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        x[i] =(- 999);
        b[i] = i;
        for(j = 0; j <= i; j++) L[i][j] =((double )(i + n - j + 1)) * 2 / n;
    }

#pragma endscop
}
