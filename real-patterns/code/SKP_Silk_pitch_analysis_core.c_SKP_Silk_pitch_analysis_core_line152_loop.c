#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int frame_length_4kHz;
extern short  signal_4kHz[960 >> 2] ;

void loop()
{
#pragma scop

    for(i = frame_length_4kHz - 1; i > 0; i--)
    {
        signal_4kHz[i] =((short )((((int )signal_4kHz[i]) + signal_4kHz[i - 1] > 0x7FFF?0x7FFF :((((int )signal_4kHz[i]) + signal_4kHz[i - 1] <((short )0x8000)?((short )0x8000) :((int )signal_4kHz[i]) + signal_4kHz[i - 1])))));
    }

#pragma endscop
}
