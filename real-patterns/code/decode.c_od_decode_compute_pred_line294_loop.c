#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int n;
extern int x;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict pred;
extern od_coeff * restrict l;

void loop()
{
#pragma scop

    for(y = 0; y < n; y++)
    {
        for(x = 0; x < n; x++)
        {
            pred[n * y + x] = l[n * y + x];
        }
    }

#pragma endscop
}
