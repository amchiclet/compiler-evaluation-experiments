#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int d;
extern int * restrict ar;
extern int tmp_chirp_Q16;
extern int chirp_Q16;

void loop()
{
#pragma scop

    for(i = 0; i < d - 1; i++)
    {
        ar[i] =(ar[i] >> 16) *((int )((short )tmp_chirp_Q16)) +((ar[i] & 0x0000FFFF) *((int )((short )tmp_chirp_Q16)) >> 16) + ar[i] *((16 == 1?(tmp_chirp_Q16 >> 1) +(tmp_chirp_Q16 & 1) :(tmp_chirp_Q16 >> 16 - 1) + 1 >> 1));
        tmp_chirp_Q16 =(chirp_Q16 >> 16) *((int )((short )tmp_chirp_Q16)) +((chirp_Q16 & 0x0000FFFF) *((int )((short )tmp_chirp_Q16)) >> 16) + chirp_Q16 *((16 == 1?(tmp_chirp_Q16 >> 1) +(tmp_chirp_Q16 & 1) :(tmp_chirp_Q16 >> 16 - 1) + 1 >> 1));
    }

#pragma endscop
}
