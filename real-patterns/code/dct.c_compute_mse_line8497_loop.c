#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int j;
extern double ret;
extern double  e[1 << 6][1 << 6] ;
extern double  basis[1 << 2 + 5 - 1][1 << 2 + 5 - 1] ;
extern double  tbasis[1 << 2 + 5 - 1][1 << 2 + 5 - 1] ;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            ret += e[i][j] *(basis[i][j] - tbasis[i][j]);
        }
    }

#pragma endscop
}
