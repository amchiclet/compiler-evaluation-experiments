#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int order;
extern int i;
extern double * restrict A_p;

void loop()
{
#pragma scop

    for(j = 0; j < order; j++) for(i = 0; i < order; i++)
        {
            A_p[i + order * j] =((double )(order * j + i));
        }

#pragma endscop
}
