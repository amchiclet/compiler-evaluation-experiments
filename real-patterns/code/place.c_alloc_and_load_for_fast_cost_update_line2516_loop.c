#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int high;
extern int ny;
extern float ** restrict chanx_place_cost_fac;
extern int * restrict chan_width_x;
extern int low;

void loop()
{
#pragma scop

    for(high = 1; high <= ny; high++)
    {
        chanx_place_cost_fac[high][high] = chan_width_x[high];
        for(low = 0; low < high; low++)
        {
            chanx_place_cost_fac[high][low] = chanx_place_cost_fac[high - 1][low] + chan_width_x[high];
        }
    }

#pragma endscop
}
