#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern short  xt[80] ;
extern short * restrict sptr;
extern int a3;
extern short * restrict tf;
extern int a2;
extern int a1;
extern int a0;
extern int b3;
extern int b2;
extern int b1;
extern int b0;
extern short * restrict optr;

void loop()
{
#pragma scop

    for(j = 0; j < 8; j++)
    {
        xt[3] =(sptr[3] + sptr[4]);
        xt[2] =(sptr[2] + sptr[5]);
        xt[1] =(sptr[1] + sptr[6]);
        xt[0] =(sptr[0] + sptr[7]);
        xt[7] =(sptr[3] - sptr[4]);
        xt[6] =(sptr[2] - sptr[5]);
        xt[5] =(sptr[1] - sptr[6]);
        xt[4] =(sptr[0] - sptr[7]);
        a3 = xt[0] * tf[6] + xt[2] * tf[7] +(xt[1] * tf[14] + xt[3] * tf[15]);
        a2 = xt[0] * tf[4] + xt[2] * tf[5] +(xt[1] * tf[12] + xt[3] * tf[13]);
        a1 = xt[0] * tf[2] + xt[2] * tf[3] +(xt[1] * tf[10] + xt[3] * tf[11]);
        a0 = xt[0] * tf[0] + xt[2] * tf[1] +(xt[1] * tf[8] + xt[3] * tf[9]);
        b3 = xt[4] * tf[22] + xt[6] * tf[23] +(xt[5] * tf[30] + xt[7] * tf[31]);
        b2 = xt[4] * tf[20] + xt[6] * tf[21] +(xt[5] * tf[28] + xt[7] * tf[29]);
        b1 = xt[4] * tf[18] + xt[6] * tf[19] +(xt[5] * tf[26] + xt[7] * tf[27]);
        b0 = xt[4] * tf[16] + xt[6] * tf[17] +(xt[5] * tf[24] + xt[7] * tf[25]);
        tf += 32;
        a3 = a3 +(1 << 2 + 17 - 1) >> 2 + 17;
        a2 = a2 +(1 << 2 + 17 - 1) >> 2 + 17;
        a1 = a1 +(1 << 2 + 17 - 1) >> 2 + 17;
        a0 = a0 +(1 << 2 + 17 - 1) >> 2 + 17;
        b3 = b3 +(1 << 2 + 17 - 1) >> 2 + 17;
        b2 = b2 +(1 << 2 + 17 - 1) >> 2 + 17;
        b1 = b1 +(1 << 2 + 17 - 1) >> 2 + 17;
        b0 = b0 +(1 << 2 + 17 - 1) >> 2 + 17;
        a3 =(a3 > 2047?2047 : a3);
        a2 =(a2 > 2047?2047 : a2);
        a1 =(a1 > 2047?2047 : a1);
        a0 =(a0 > 2047?2047 : a0);
        b3 =(b3 > 2047?2047 : b3);
        b2 =(b2 > 2047?2047 : b2);
        b1 =(b1 > 2047?2047 : b1);
        b0 =(b0 > 2047?2047 : b0);
        a3 =(a3 < - 2048?- 2048 : a3);
        a2 =(a2 < - 2048?- 2048 : a2);
        a1 =(a1 < - 2048?- 2048 : a1);
        a0 =(a0 < - 2048?- 2048 : a0);
        b3 =(b3 < - 2048?- 2048 : b3);
        b2 =(b2 < - 2048?- 2048 : b2);
        b1 =(b1 < - 2048?- 2048 : b1);
        b0 =(b0 < - 2048?- 2048 : b0);
        optr[3] = b1;
        optr[2] = a1;
        optr[1] = b0;
        optr[0] = a0;
        optr[7] = b3;
        optr[6] = a3;
        optr[5] = b2;
        optr[4] = a2;
        sptr += 8;
        optr += 8;
    }

#pragma endscop
}
