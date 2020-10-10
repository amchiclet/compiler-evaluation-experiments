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
        x[i] = b[i];
        for(j = 0; j < i; j++) x[i] -= L[i][j] * x[j];
        x[i] = x[i] / L[i][i];
    }

#pragma endscop
}
