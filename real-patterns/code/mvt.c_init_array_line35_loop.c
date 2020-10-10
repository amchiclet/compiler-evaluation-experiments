#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double  x1[2000 + 0] ;
extern double  x2[2000 + 0] ;
extern double  y_1[2000 + 0] ;
extern double  y_2[2000 + 0] ;
extern int j;
extern double  A[2000 + 0][2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        x1[i] =((double )(i % n)) / n;
        x2[i] =((double )((i + 1) % n)) / n;
        y_1[i] =((double )((i + 3) % n)) / n;
        y_2[i] =((double )((i + 4) % n)) / n;
        for(j = 0; j < n; j++) A[i][j] =((double )(i * j % n)) / n;
    }

#pragma endscop
}
