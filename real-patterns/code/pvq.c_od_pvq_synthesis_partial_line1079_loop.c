#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef int int32_t;
typedef int32_t od_val32;
typedef short int16_t;
typedef int32_t od_coeff;
extern od_coeff * restrict ypulse;
typedef long int64_t;
extern od_val32 scale;
extern od_coeff * restrict xcoeff;
extern int16_t * restrict qm_inv;
extern int qshift;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        od_val32 x;
        x =(((int16_t )ypulse[i]) *((int64_t )((int32_t )scale)) >> 16);
        xcoeff[i] =((int32_t )(x * qm_inv[i] +(1 << qshift >> 1) >> qshift));
    }

#pragma endscop
}
