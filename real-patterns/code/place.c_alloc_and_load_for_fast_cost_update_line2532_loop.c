#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int high;
extern int ny;
extern int low;
extern float ** restrict chanx_place_cost_fac;
extern float place_cost_exp;

void loop()
{
#pragma scop

    for(high = 0; high <= ny; high++) for(low = 0; low <= high; low++)
        {
            chanx_place_cost_fac[high][low] =(((high - low) + 1.0) / chanx_place_cost_fac[high][low]);
            chanx_place_cost_fac[high][low] =(pow(((double )chanx_place_cost_fac[high][low]),((double )place_cost_exp)));
        }

#pragma endscop
}
