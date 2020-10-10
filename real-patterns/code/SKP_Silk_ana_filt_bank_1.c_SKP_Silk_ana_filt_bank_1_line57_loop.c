#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int N2;
extern int in32;
extern short * restrict in;
extern int Y;
extern int * restrict S;
extern int X;
extern short  A_fb1_21[1] ;
extern int out_1;
extern short  A_fb1_20[1] ;
extern int out_2;
extern short * restrict outL;
extern short * restrict outH;

void loop()
{
#pragma scop

    for(k = 0; k < N2; k++)
    {
        in32 =((int )in[2 * k]) << 10;
        Y = in32 - S[0];
        X = Y +((Y >> 16) *((int )((short )A_fb1_21[0])) +((Y & 0x0000FFFF) *((int )((short )A_fb1_21[0])) >> 16));
        out_1 = S[0] + X;
        S[0] = in32 + X;
        in32 =((int )in[2 * k + 1]) << 10;
        Y = in32 - S[1];
        X =(Y >> 16) *((int )((short )A_fb1_20[0])) +((Y & 0x0000FFFF) *((int )((short )A_fb1_20[0])) >> 16);
        out_2 = S[1] + X;
        S[1] = in32 + X;
        outL[k] =((short )((((11 == 1?(out_2 + out_1 >> 1) +(out_2 + out_1 & 1) :(out_2 + out_1 >> 11 - 1) + 1 >> 1)) > 0x7FFF?0x7FFF :((((11 == 1?(out_2 + out_1 >> 1) +(out_2 + out_1 & 1) :(out_2 + out_1 >> 11 - 1) + 1 >> 1)) <((short )0x8000)?((short )0x8000) :((11 == 1?(out_2 + out_1 >> 1) +(out_2 + out_1 & 1) :(out_2 + out_1 >> 11 - 1) + 1 >> 1)))))));
        outH[k] =((short )((((11 == 1?(out_2 - out_1 >> 1) +(out_2 - out_1 & 1) :(out_2 - out_1 >> 11 - 1) + 1 >> 1)) > 0x7FFF?0x7FFF :((((11 == 1?(out_2 - out_1 >> 1) +(out_2 - out_1 & 1) :(out_2 - out_1 >> 11 - 1) + 1 >> 1)) <((short )0x8000)?((short )0x8000) :((11 == 1?(out_2 - out_1 >> 1) +(out_2 - out_1 & 1) :(out_2 - out_1 >> 11 - 1) + 1 >> 1)))))));
    }

#pragma endscop
}
