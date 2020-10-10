#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int length;
extern short* restrict signal;
extern int gain_Q12;
extern int slope_Q12;

void loop()
{
#pragma scop

    for(i = 0; i < length; i++)
    {
        signal[i] =(gain_Q12 * signal[i] >> 12);
        gain_Q12 += slope_Q12;
        gain_Q12 =(gain_Q12 < 1 << 12?gain_Q12 : 1 << 12);
    }

#pragma endscop
}
