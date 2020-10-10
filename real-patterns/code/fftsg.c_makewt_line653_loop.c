#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nwh;
extern double * restrict w;
extern double delta;

void loop()
{
#pragma scop

    for(j = 4; j < nwh; j += 4)
    {
        w[j] = cos(delta * j);
        w[j + 1] = sin(delta * j);
        w[j + 2] = cos(3 * delta * j);
        w[j + 3] = sin(3 * delta * j);
    }

#pragma endscop
}
