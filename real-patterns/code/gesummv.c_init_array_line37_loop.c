#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  x[1300 + 0] ;
extern int j;
extern double  A[1300 + 0][1300 + 0] ;
extern double  B[1300 + 0][1300 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        x[i] =((double )(i % n)) / n;
        for(j = 0; j < n; j++)
        {
            A[i][j] =((double )(i * j % n)) / n;
            B[i][j] =((double )(i * j % n)) / n;
        }
    }

#pragma endscop
}
