#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int D;
extern int Atmp1;
extern int  Af_QA[16] ;
extern int nrg;
extern int  CAf[16 + 1] ;
extern int tmp1;
extern int* restrict A_Q16;

void loop()
{
#pragma scop

    for(k = 0; k < D; k++)
    {
        Atmp1 =(25 - 16 == 1?(Af_QA[k] >> 1) +(Af_QA[k] & 1) :(Af_QA[k] >> 25 - 16 - 1) + 1 >> 1);
        nrg = nrg +((CAf[k + 1] >> 16) *((int )((short )Atmp1)) +((CAf[k + 1] & 0x0000FFFF) *((int )((short )Atmp1)) >> 16)) + CAf[k + 1] *((16 == 1?(Atmp1 >> 1) +(Atmp1 & 1) :(Atmp1 >> 16 - 1) + 1 >> 1));
        tmp1 = tmp1 +((Atmp1 >> 16) *((int )((short )Atmp1)) +((Atmp1 & 0x0000FFFF) *((int )((short )Atmp1)) >> 16)) + Atmp1 *((16 == 1?(Atmp1 >> 1) +(Atmp1 & 1) :(Atmp1 >> 16 - 1) + 1 >> 1));
        A_Q16[k] = -Atmp1;
    }

#pragma endscop
}
