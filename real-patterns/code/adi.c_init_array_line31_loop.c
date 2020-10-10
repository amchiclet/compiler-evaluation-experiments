#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double  u[1000 + 0][1000 + 0] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++) for(j = 0; j < n; j++)
        {
            u[i][j] =((double )(i + n - j)) / n;
        }

#pragma endscop
}
