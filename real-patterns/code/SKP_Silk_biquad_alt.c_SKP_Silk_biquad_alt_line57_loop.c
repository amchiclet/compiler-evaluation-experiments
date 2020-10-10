#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int len;
extern int inval;
extern short * restrict in;
extern int out32_Q14;
extern int * restrict S;
extern int * restrict B_Q28;
extern int A0_L_Q28;
extern int A0_U_Q28;
extern int A1_L_Q28;
extern int A1_U_Q28;
extern short * restrict out;

void loop()
{
#pragma scop

    for(k = 0; k < len; k++)
    {
        inval = in[k];
        out32_Q14 = S[0] +((B_Q28[0] >> 16) *((int )((short )inval)) +((B_Q28[0] & 0x0000FFFF) *((int )((short )inval)) >> 16)) << 2;
        S[0] = S[1] +((14 == 1?((out32_Q14 >> 16) *((int )((short )A0_L_Q28)) +((out32_Q14 & 0x0000FFFF) *((int )((short )A0_L_Q28)) >> 16) >> 1) +((out32_Q14 >> 16) *((int )((short )A0_L_Q28)) +((out32_Q14 & 0x0000FFFF) *((int )((short )A0_L_Q28)) >> 16) & 1) :((out32_Q14 >> 16) *((int )((short )A0_L_Q28)) +((out32_Q14 & 0x0000FFFF) *((int )((short )A0_L_Q28)) >> 16) >> 14 - 1) + 1 >> 1));
        S[0] = S[0] +((out32_Q14 >> 16) *((int )((short )A0_U_Q28)) +((out32_Q14 & 0x0000FFFF) *((int )((short )A0_U_Q28)) >> 16));
        S[0] = S[0] +((B_Q28[1] >> 16) *((int )((short )inval)) +((B_Q28[1] & 0x0000FFFF) *((int )((short )inval)) >> 16));
        S[1] =(14 == 1?((out32_Q14 >> 16) *((int )((short )A1_L_Q28)) +((out32_Q14 & 0x0000FFFF) *((int )((short )A1_L_Q28)) >> 16) >> 1) +((out32_Q14 >> 16) *((int )((short )A1_L_Q28)) +((out32_Q14 & 0x0000FFFF) *((int )((short )A1_L_Q28)) >> 16) & 1) :((out32_Q14 >> 16) *((int )((short )A1_L_Q28)) +((out32_Q14 & 0x0000FFFF) *((int )((short )A1_L_Q28)) >> 16) >> 14 - 1) + 1 >> 1);
        S[1] = S[1] +((out32_Q14 >> 16) *((int )((short )A1_U_Q28)) +((out32_Q14 & 0x0000FFFF) *((int )((short )A1_U_Q28)) >> 16));
        S[1] = S[1] +((B_Q28[2] >> 16) *((int )((short )inval)) +((B_Q28[2] & 0x0000FFFF) *((int )((short )inval)) >> 16));
        out[k] =((short )((out32_Q14 +(1 << 14) - 1 >> 14 > 0x7FFF?0x7FFF :((out32_Q14 +(1 << 14) - 1 >> 14 <((short )0x8000)?((short )0x8000) : out32_Q14 +(1 << 14) - 1 >> 14)))));
    }

#pragma endscop
}
