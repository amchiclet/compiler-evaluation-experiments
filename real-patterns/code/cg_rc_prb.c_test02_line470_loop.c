#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double t;
extern double * restrict x_exact;
extern double * restrict x;
extern double err;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        t = fabs(x_exact[i] - x[i]);
        if(err < t)
        {
            err = t;
        }
    }

#pragma endscop
}
