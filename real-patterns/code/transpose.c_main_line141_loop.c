#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int order;
extern int i;
extern double * restrict B_p;

void loop()
{
#pragma scop

    for(j = 0; j < order; j++) for(i = 0; i < order; i++)
        {
            B_p[i + order * j] = - 1.0;
        }

#pragma endscop
}
