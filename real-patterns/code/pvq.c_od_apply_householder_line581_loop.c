#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef int int32_t;
typedef int32_t od_val32;
extern od_val32 proj;
typedef short int16_t;
typedef int16_t od_val16;
extern od_val16 * restrict r;
extern od_val16 * restrict x;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        proj +=((od_val32 )((od_val16 )r[i])) *((od_val32 )((od_val16 )x[i]));
    }

#pragma endscop
}
