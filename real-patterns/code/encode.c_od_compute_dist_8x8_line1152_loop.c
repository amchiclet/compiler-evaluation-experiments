#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff  e[8 * 8] ;
extern od_coeff * restrict x;
extern int stride;
extern od_coeff * restrict y;

void loop()
{
#pragma scop

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++) e[8 * i + j] = x[i * stride + j] - y[i * stride + j];
    }

#pragma endscop
}
