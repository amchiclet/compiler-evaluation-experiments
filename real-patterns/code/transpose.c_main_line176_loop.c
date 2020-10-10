#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int order;
extern int i;
extern double abserr;
extern double * restrict B_p;

void loop()
{
#pragma scop

    for(j = 0; j < order; j++) for(i = 0; i < order; i++)
        {
            abserr +=(B_p[i + order * j] -((double )(order * i + j)) >= 0?B_p[i + order * j] -((double )(order * i + j)) : -(B_p[i + order * j] -((double )(order * i + j))));
        }

#pragma endscop
}
