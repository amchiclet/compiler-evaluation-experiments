#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int d;
extern short * restrict ar;
extern int chirp_Q16;
extern int chirp_minus_one_Q16;

void loop()
{
#pragma scop

    for(i = 0; i < d - 1; i++)
    {
        ar[i] =((short )((16 == 1?(chirp_Q16 * ar[i] >> 1) +(chirp_Q16 * ar[i] & 1) :(chirp_Q16 * ar[i] >> 16 - 1) + 1 >> 1)));
        chirp_Q16 +=(16 == 1?(chirp_Q16 * chirp_minus_one_Q16 >> 1) +(chirp_Q16 * chirp_minus_one_Q16 & 1) :(chirp_Q16 * chirp_minus_one_Q16 >> 16 - 1) + 1 >> 1);
    }

#pragma endscop
}
