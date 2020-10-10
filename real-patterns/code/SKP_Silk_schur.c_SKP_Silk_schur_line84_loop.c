#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int order;
extern int k;
extern int Ctmp1;
extern int  C[16 + 1][2] ;
extern int Ctmp2;
extern int rc_tmp_Q15;

void loop()
{
#pragma scop

    for(n = 0; n < order - k; n++)
    {
        Ctmp1 = C[n + k + 1][0];
        Ctmp2 = C[n][1];
        C[n + k + 1][0] = Ctmp1 +((Ctmp2 << 1 >> 16) *((int )((short )rc_tmp_Q15)) +((Ctmp2 << 1 & 0x0000FFFF) *((int )((short )rc_tmp_Q15)) >> 16));
        C[n][1] = Ctmp2 +((Ctmp1 << 1 >> 16) *((int )((short )rc_tmp_Q15)) +((Ctmp1 << 1 & 0x0000FFFF) *((int )((short )rc_tmp_Q15)) >> 16));
    }

#pragma endscop
}
