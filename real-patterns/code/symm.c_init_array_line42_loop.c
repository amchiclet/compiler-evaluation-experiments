#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern double  A[1000 + 0][1000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++)
    {
        for(j = 0; j <= i; j++) A[i][j] =((double )((i + j) % 100)) / m;
        for(j = i + 1; j < m; j++) A[i][j] =(- 999);
    }

#pragma endscop
}
