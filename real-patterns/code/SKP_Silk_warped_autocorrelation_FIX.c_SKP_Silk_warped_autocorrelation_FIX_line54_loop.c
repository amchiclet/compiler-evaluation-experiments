#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int length;
extern int tmp1_QS;
extern short * restrict input;
extern int i;
extern int order;
extern int tmp2_QS;
extern int  state_QS[16 + 1] ;
extern short warping_Q16;
typedef long int64_t;
extern int64_t  corr_QC[16 + 1] ;

void loop()
{
#pragma scop

    for(n = 0; n < length; n++)
    {
        tmp1_QS =((int )input[n]) << 14;
        for(i = 0; i < order; i += 2)
        {
            tmp2_QS = state_QS[i] +((state_QS[i + 1] - tmp1_QS >> 16) *((int )((short )warping_Q16)) +((state_QS[i + 1] - tmp1_QS & 0x0000FFFF) *((int )((short )warping_Q16)) >> 16));
            state_QS[i] = tmp1_QS;
            corr_QC[i] +=((int64_t )tmp1_QS) * state_QS[0] >> 2 * 14 - 10;
            tmp1_QS = state_QS[i + 1] +((state_QS[i + 2] - tmp2_QS >> 16) *((int )((short )warping_Q16)) +((state_QS[i + 2] - tmp2_QS & 0x0000FFFF) *((int )((short )warping_Q16)) >> 16));
            state_QS[i + 1] = tmp2_QS;
            corr_QC[i + 1] +=((int64_t )tmp2_QS) * state_QS[0] >> 2 * 14 - 10;
        }
        state_QS[order] = tmp1_QS;
        corr_QC[order] +=((int64_t )tmp1_QS) * state_QS[0] >> 2 * 14 - 10;
    }

#pragma endscop
}
