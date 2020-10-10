#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int order;
extern int * restrict coefs_syn_Q24;
extern int gain_syn_Q16;
extern int * restrict coefs_ana_Q24;
extern int gain_ana_Q16;

void loop()
{
#pragma scop

    for(i = 0; i < order; i++)
    {
        coefs_syn_Q24[i] =(gain_syn_Q16 >> 16) *((int )((short )coefs_syn_Q24[i])) +((gain_syn_Q16 & 0x0000FFFF) *((int )((short )coefs_syn_Q24[i])) >> 16) + gain_syn_Q16 *((16 == 1?(coefs_syn_Q24[i] >> 1) +(coefs_syn_Q24[i] & 1) :(coefs_syn_Q24[i] >> 16 - 1) + 1 >> 1));
        coefs_ana_Q24[i] =(gain_ana_Q16 >> 16) *((int )((short )coefs_ana_Q24[i])) +((gain_ana_Q16 & 0x0000FFFF) *((int )((short )coefs_ana_Q24[i])) >> 16) + gain_ana_Q16 *((16 == 1?(coefs_ana_Q24[i] >> 1) +(coefs_ana_Q24[i] & 1) :(coefs_ana_Q24[i] >> 16 - 1) + 1 >> 1));
    }

#pragma endscop
}
