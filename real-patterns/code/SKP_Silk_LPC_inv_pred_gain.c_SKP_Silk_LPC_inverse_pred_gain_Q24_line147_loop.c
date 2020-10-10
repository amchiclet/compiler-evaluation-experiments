#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int order;
extern int * restrict Anew_QA;
extern int * restrict A_Q24;

void loop()
{
#pragma scop

    for(k = 0; k < order; k++)
    {
        Anew_QA[k] =(24 - 16 == 1?(A_Q24[k] >> 1) +(A_Q24[k] & 1) :(A_Q24[k] >> 24 - 16 - 1) + 1 >> 1);
    }

#pragma endscop
}
