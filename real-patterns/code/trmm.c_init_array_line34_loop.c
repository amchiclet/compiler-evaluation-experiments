#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern double  A[1000 + 0][1000 + 0] ;
extern int n;
extern double  B[1000 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < i; j++)
        {
            A[i][j] =((double )((i + j) % m)) / m;
        }
        A[i][i] = 1.0;
        for(j = 0; j < n; j++)
        {
            B[i][j] =((double )((n +(i - j)) % n)) / n;
        }
    }

#pragma endscop
}
