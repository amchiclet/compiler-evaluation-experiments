#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int order;
extern int * restrict coefs_syn_Q24;
extern int lambda_Q16;
extern int * restrict coefs_ana_Q24;

void loop()
{
#pragma scop

    for(i = 1; i < order; i++)
    {
        coefs_syn_Q24[i - 1] = coefs_syn_Q24[i - 1] +((coefs_syn_Q24[i] >> 16) *((int )((short )lambda_Q16)) +((coefs_syn_Q24[i] & 0x0000FFFF) *((int )((short )lambda_Q16)) >> 16));
        coefs_ana_Q24[i - 1] = coefs_ana_Q24[i - 1] +((coefs_ana_Q24[i] >> 16) *((int )((short )lambda_Q16)) +((coefs_ana_Q24[i] & 0x0000FFFF) *((int )((short )lambda_Q16)) >> 16));
    }

#pragma endscop
}
