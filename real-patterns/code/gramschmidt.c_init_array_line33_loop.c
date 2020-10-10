#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int m;
extern int j;
extern int n;
extern double  A[1000 + 0][1200 + 0] ;
extern double  Q[1000 + 0][1200 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < m; i++) for(j = 0; j < n; j++)
        {
            A[i][j] =((double )(i * j % m)) / m * 100 + 10;
            Q[i][j] = 0.0;
        }

#pragma endscop
}
