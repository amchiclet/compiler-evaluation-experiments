#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int w_size;
extern double * restrict g;
extern double * restrict w;

void loop()
{
#pragma scop

    for(i = 0; i < w_size; i++) g[i] = w[i] + 2 * g[i];

#pragma endscop
}
