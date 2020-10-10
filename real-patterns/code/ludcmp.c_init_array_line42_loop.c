#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  A[2000 + 0][2000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j <= i; j++) A[i][j] =((double )(-j % n)) / n + 1;
        for(j = i + 1; j < n; j++)
        {
            A[i][j] = 0;
        }
        A[i][i] = 1;
    }

#pragma endscop
}
