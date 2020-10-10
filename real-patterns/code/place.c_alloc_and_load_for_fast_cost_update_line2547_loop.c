#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int high;
extern int nx;
extern float ** restrict chany_place_cost_fac;
extern int * restrict chan_width_y;
extern int low;

void loop()
{
#pragma scop

    for(high = 1; high <= nx; high++)
    {
        chany_place_cost_fac[high][high] = chan_width_y[high];
        for(low = 0; low < high; low++)
        {
            chany_place_cost_fac[high][low] = chany_place_cost_fac[high - 1][low] + chan_width_y[high];
        }
    }

#pragma endscop
}
