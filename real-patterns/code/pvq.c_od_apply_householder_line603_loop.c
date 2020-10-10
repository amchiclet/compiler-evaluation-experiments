#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef int int32_t;
typedef int32_t od_val32;
typedef short int16_t;
typedef int16_t od_val16;
extern od_val16 * restrict r;
extern od_val16 proj_1;
extern int outshift;
extern od_val16 * restrict out;
extern od_val16 * restrict x;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        int32_t tmp;
        tmp =((od_val32 )((od_val16 )r[i])) *((od_val32 )((od_val16 )proj_1));
        tmp =((int32_t )(tmp +(1 << outshift >> 1) >> outshift));
        out[i] =(x[i] - tmp);
    }

#pragma endscop
}
