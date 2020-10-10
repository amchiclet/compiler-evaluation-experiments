#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int len;
extern int SA;
extern int * restrict S;
extern int SB;
extern int out32_Q10;
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
        SA = S[15];
        SB = S[14];
        S[14] = SA;
        out32_Q10 =(SA >> 16) *((int )((short )A_Q12[0])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[0])) >> 16);
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SB >> 16) *((int )((short )A_Q12[1])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[1])) >> 16)))));
        SA = S[13];
        S[13] = SB;
        SB = S[12];
        S[12] = SA;
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SA >> 16) *((int )((short )A_Q12[2])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[2])) >> 16)))));
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SB >> 16) *((int )((short )A_Q12[3])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[3])) >> 16)))));
        SA = S[11];
        S[11] = SB;
        SB = S[10];
        S[10] = SA;
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SA >> 16) *((int )((short )A_Q12[4])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[4])) >> 16)))));
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SB >> 16) *((int )((short )A_Q12[5])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[5])) >> 16)))));
        SA = S[9];
        S[9] = SB;
        SB = S[8];
        S[8] = SA;
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SA >> 16) *((int )((short )A_Q12[6])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[6])) >> 16)))));
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SB >> 16) *((int )((short )A_Q12[7])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[7])) >> 16)))));
        SA = S[7];
        S[7] = SB;
        SB = S[6];
        S[6] = SA;
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SA >> 16) *((int )((short )A_Q12[8])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[8])) >> 16)))));
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SB >> 16) *((int )((short )A_Q12[9])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[9])) >> 16)))));
        SA = S[5];
        S[5] = SB;
        SB = S[4];
        S[4] = SA;
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SA >> 16) *((int )((short )A_Q12[10])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[10])) >> 16)))));
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SB >> 16) *((int )((short )A_Q12[11])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[11])) >> 16)))));
        SA = S[3];
        S[3] = SB;
        SB = S[2];
        S[2] = SA;
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SA >> 16) *((int )((short )A_Q12[12])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[12])) >> 16)))));
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SB >> 16) *((int )((short )A_Q12[13])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[13])) >> 16)))));
        SA = S[1];
        S[1] = SB;
        SB = S[0];
        S[0] = SA;
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SA >> 16) *((int )((short )A_Q12[14])) +((SA & 0x0000FFFF) *((int )((short )A_Q12[14])) >> 16)))));
        out32_Q10 =((int )(((unsigned int )out32_Q10) +((unsigned int )((SB >> 16) *((int )((short )A_Q12[15])) +((SB & 0x0000FFFF) *((int )((short )A_Q12[15])) >> 16)))));
        out32_Q10 =(((out32_Q10 +((Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16))) & 0x80000000) == 0?((((out32_Q10 &(Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16)) & 0x80000000) != 0?((int )0x80000000) : out32_Q10 +((Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16)))) :((((out32_Q10 |(Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16)) & 0x80000000) == 0?0x7FFFFFFF : out32_Q10 +((Gain_Q26 >> 16) *((int )((short )in[k])) +((Gain_Q26 & 0x0000FFFF) *((int )((short )in[k])) >> 16)))));
        out32 =(10 == 1?(out32_Q10 >> 1) +(out32_Q10 & 1) :(out32_Q10 >> 10 - 1) + 1 >> 1);
        out[k] =((short )((out32 > 0x7FFF?0x7FFF :((out32 <((short )0x8000)?((short )0x8000) : out32)))));
        S[15] =((((int )0x80000000) >> 4 > 0x7FFFFFFF >> 4?((out32_Q10 >((int )0x80000000) >> 4?((int )0x80000000) >> 4 :((out32_Q10 < 0x7FFFFFFF >> 4?0x7FFFFFFF >> 4 : out32_Q10)))) :((out32_Q10 > 0x7FFFFFFF >> 4?0x7FFFFFFF >> 4 :((out32_Q10 <((int )0x80000000) >> 4?((int )0x80000000) >> 4 : out32_Q10)))))) << 4;
    }

#pragma endscop
}
