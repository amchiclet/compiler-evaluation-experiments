#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict xcoeff;
typedef short int16_t;
typedef int16_t od_val16;
extern od_val16  x[4096 / 2] ;
extern int16_t * restrict qm_inv;
extern int qshift;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        xcoeff[i] =((int32_t )(x[i] * qm_inv[i] +(1 << qshift >> 1) >> qshift));
    }

#pragma endscop
}
