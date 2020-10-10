#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int n;
extern int x;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict output;
extern int w;
typedef short int16_t;
extern int16_t  buf[64 * 64] ;

void loop()
{
#pragma scop

    for(y = 0; y < n; y++)
    {
        for(x = 0; x < n; x++)
        {
            output[y * w + x] = buf[y * n + x];
        }
    }

#pragma endscop
}
