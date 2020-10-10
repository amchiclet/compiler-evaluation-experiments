#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern double * restrict r;
extern double * restrict ax;

void loop()
{
#pragma scop

    for(i = 0; i < n; i++)
    {
        r[i] = r[i] - ax[i];
    }

#pragma endscop
}
