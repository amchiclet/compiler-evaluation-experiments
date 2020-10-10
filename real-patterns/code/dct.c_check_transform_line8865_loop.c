#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int n;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff  x[1 << 6] ;
extern double  basis[1 << 6][1 << 6] ;
extern int i;

void loop()
{
#pragma scop

    for(j = 0; j < n; j++)
    {
        x[j] =(basis[j][i] < 0?- 256 : 255);
    }

#pragma endscop
}
