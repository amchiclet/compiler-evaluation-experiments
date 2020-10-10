#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nch;
extern double * restrict c;
extern double delta;
extern int nc;

void loop()
{
#pragma scop

    for(j = 1; j < nch; j++)
    {
        c[j] = 0.5 * cos(delta * j);
        c[nc - j] = 0.5 * sin(delta * j);
    }

#pragma endscop
}
