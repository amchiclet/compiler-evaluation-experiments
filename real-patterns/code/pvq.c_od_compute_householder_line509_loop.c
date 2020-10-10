#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
typedef short int16_t;
typedef int16_t od_val16;
extern od_val16 * restrict r;
extern od_val16 maxr;
extern int m;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        if(abs(r[i]) > maxr)
        {
            maxr =(abs(r[i]));
            m = i;
        }
    }

#pragma endscop
}
