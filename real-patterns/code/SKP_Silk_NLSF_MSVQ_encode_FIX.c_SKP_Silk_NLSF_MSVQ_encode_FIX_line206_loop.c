#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int LPC_order;
extern int se_Q15;
extern int * restrict pNLSF_Q15;
extern int * restrict pNLSF_q_Q15_prev;
extern int wsse_Q20;
extern int * restrict pW_Q6;

void loop()
{
#pragma scop

    for(i = 0; i < LPC_order; i += 2)
    {
        se_Q15 = pNLSF_Q15[i] - pNLSF_q_Q15_prev[i];
        wsse_Q20 = wsse_Q20 +((((int )((short )se_Q15)) *((int )((short )se_Q15)) >> 16) *((int )((short )pW_Q6[i])) +((((int )((short )se_Q15)) *((int )((short )se_Q15)) & 0x0000FFFF) *((int )((short )pW_Q6[i])) >> 16));
        se_Q15 = pNLSF_Q15[i + 1] - pNLSF_q_Q15_prev[i + 1];
        wsse_Q20 = wsse_Q20 +((((int )((short )se_Q15)) *((int )((short )se_Q15)) >> 16) *((int )((short )pW_Q6[i + 1])) +((((int )((short )se_Q15)) *((int )((short )se_Q15)) & 0x0000FFFF) *((int )((short )pW_Q6[i + 1])) >> 16));
    }

#pragma endscop
}
