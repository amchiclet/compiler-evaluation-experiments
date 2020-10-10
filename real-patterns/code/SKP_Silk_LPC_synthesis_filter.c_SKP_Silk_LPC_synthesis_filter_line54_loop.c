#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int len;
extern int SA;
extern int * restrict S;
extern int Order;
extern int out32_Q10;
extern int j;
extern int Order_half;
extern int idx;
extern int SB;
extern short * restrict A_Q12;
extern int Gain_Q26;
extern short * restrict in;
extern int out32;
extern short * restrict out;

void loop()
{
#pragma scop

    for(k = 0; k < len; k++)
    {
        SA = S[Order - 1];
        out32_Q10 = 0;
        for(j = 0; j < Order_half - 1; j++)
        {
            idx =((int )((short )2)) *((int )((short )j)) + 1;
            SB = S[Order - 1 - idx];
            S[Order - 1 - idx] = SA;
            out32_Q10 = out32_Q10 +((SA >> 16) *((int )((short )A_Q12[j << 1])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[j << 1])) >> 16));
            out32_Q10 = out32_Q10 +((SB >> 16) *((int )((short )A_Q12[(j << 1) + 1])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[(j << 1) + 1])) >> 16));
            SA = S[Order - 2 - idx];
            S[Order - 2 - idx] = SB;
        }
        SB = S[0];
        S[0] = SA;
        out32_Q10 = out32_Q10 +((SA >> 16) *((int )((short )A_Q12[Order - 2])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[Order - 2])) >> 16));
        out32_Q10 = out32_Q10 +((SB >> 16) *((int )((short )A_Q12[Order - 1])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[Order - 1])) >> 16));
        out32_Q10 =(((out32_Q10 +((Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16))) & 0x80000000) == 0?((((out32_Q10 &(Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16)) & 0x80000000) != 0?((int )0x80000000) : out32_Q10 +((Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16)))) :((((out32_Q10 |(Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16)) & 0x80000000) == 0?0x7FFFFFFF : out32_Q10 +((Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16)))));
        out32 =(10 == 1?(out32_Q10 >> 1) +(out32_Q10 & 1) :(out32_Q10 >> 10 - 1) + 1 >> 1);
        out[k] =((short )((out32 > 0x7FFF?0x7FFF :((out32 <((short )0x8000)?((short )0x8000) : out32)))));
        S[Order - 1] =((((int )0x80000000) >> 4 > 0x7FFFFFFF >> 4?((out32_Q10 >((int )0x80000000) >> 4?((int )0x80000000) >> 4 :((out32_Q10 < 0x7FFFFFFF >> 4?0x7FFFFFFF >> 4 : out32_Q10)))) :((out32_Q10 > 0x7FFFFFFF >> 4?0x7FFFFFFF >> 4 :((out32_Q10 <((int )0x80000000) >> 4?((int )0x80000000) >> 4 : out32_Q10)))))) << 4;
    }

#pragma endscop
}
