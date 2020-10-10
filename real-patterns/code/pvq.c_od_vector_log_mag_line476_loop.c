#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef short int16_t;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict x;
extern int32_t sum;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        int16_t tmp;
        tmp =(x[i] >> 8);
        sum += tmp *((int32_t )tmp);
    }

#pragma endscop
}
