#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int frame_length;
extern short * restrict input_signal_ptr;
extern short * restrict signal;
extern int shift;

void loop()
{
#pragma scop

    for(i = 0; i < frame_length; i++)
    {
        input_signal_ptr[i] =(signal[i] >> shift);
    }

#pragma endscop
}
