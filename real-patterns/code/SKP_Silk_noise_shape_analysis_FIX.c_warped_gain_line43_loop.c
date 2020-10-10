#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int order;
extern int gain_Q24;
extern int * restrict coefs_Q24;
extern int lambda_Q16;

void loop()
{
#pragma scop

    for(i = order - 2; i >= 0; i--)
    {
        gain_Q24 = coefs_Q24[i] +((gain_Q24 >> 16) *((int )((short )lambda_Q16)) +((gain_Q24 & 0x0000FFFF) *((int )((short )lambda_Q16)) >> 16));
    }

#pragma endscop
}
