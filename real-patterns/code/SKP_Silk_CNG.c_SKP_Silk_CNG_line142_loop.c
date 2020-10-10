#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int length;
extern int tmp_32;
extern short* restrict signal;
extern short  CNG_sig[20 * 24] ;

void loop()
{
#pragma scop

    for(i = 0; i < length; i++)
    {
        tmp_32 = signal[i] + CNG_sig[i];
        signal[i] =((tmp_32 > 0x7FFF?0x7FFF :((tmp_32 <((short )0x8000)?((short )0x8000) : tmp_32))));
    }

#pragma endscop
}
