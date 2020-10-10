#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern int n;
extern double  C[1000 + 0][1200 + 0] ;
extern double  B[1000 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) for(j = 0; j < n; j++)
        {
            C[i][j] =((double )((i + j) % 100)) / m;
            B[i][j] =((double )((n + i - j) % 100)) / m;
        }

#pragma endscop
}
