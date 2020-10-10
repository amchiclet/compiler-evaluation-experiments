#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int high;
extern int nx;
extern int low;
extern float ** restrict chany_place_cost_fac;
extern float place_cost_exp;

void loop()
{
#pragma scop

    for(high = 0; high <= nx; high++) for(low = 0; low <= high; low++)
        {
            chany_place_cost_fac[high][low] =(((high - low) + 1.0) / chany_place_cost_fac[high][low]);
            chany_place_cost_fac[high][low] =(pow(((double )chany_place_cost_fac[high][low]),((double )place_cost_exp)));
        }

#pragma endscop
}
