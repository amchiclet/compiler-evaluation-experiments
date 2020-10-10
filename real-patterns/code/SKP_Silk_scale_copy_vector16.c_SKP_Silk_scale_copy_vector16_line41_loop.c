#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int dataSize;
extern int tmp32;
extern int gain_Q16;
extern short * restrict data_in;
extern short * restrict data_out;

void loop()
{
#pragma scop

    for(i = 0; i < dataSize; i++)
    {
        tmp32 =(gain_Q16 >> 16) *((int )((short )data_in[i])) +((gain_Q16 & 0x0000FFFF) *((int )((short )data_in[i])) >> 16);
        data_out[i] =((short )tmp32);
    }

#pragma endscop
}
