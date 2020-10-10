#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict x;
extern int stride;
extern int sum;
extern int s2;

void loop()
{
#pragma scop

    for(i = 0; i < 4; i++)
    {
        int j;
        for(j = 0; j < 4; j++)
        {
            int t;
            t = x[i * stride + j] >> 2;
            sum += t;
            s2 += t * t;
        }
    }

#pragma endscop
}
