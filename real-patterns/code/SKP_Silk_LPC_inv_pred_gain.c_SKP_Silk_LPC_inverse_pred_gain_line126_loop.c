#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int order;
extern int * restrict Anew_QA;
extern short * restrict A_Q12;

void loop()
{
#pragma scop

    for(k = 0; k < order; k++)
    {
        Anew_QA[k] =((int )A_Q12[k]) << 16 - 12;
    }

#pragma endscop
}
