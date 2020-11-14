#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long JLONG;
extern JLONG i;
extern JLONG * restrict rgb_ycc_tab;

void loop()
{
#pragma scop

    for(i = 0; i <= 255; i++)
    {
        rgb_ycc_tab[i + 0] =((JLONG )(0.29900 *(1L << 16) + 0.5)) * i;
        rgb_ycc_tab[i +(1 *(255 + 1))] =((JLONG )(0.58700 *(1L << 16) + 0.5)) * i;
        rgb_ycc_tab[i +(2 *(255 + 1))] =((JLONG )(0.11400 *(1L << 16) + 0.5)) * i +(((JLONG )1) << 16 - 1);
        rgb_ycc_tab[i +(3 *(255 + 1))] = -((JLONG )(0.16874 *(1L << 16) + 0.5)) * i;
        rgb_ycc_tab[i +(4 *(255 + 1))] = -((JLONG )(0.33126 *(1L << 16) + 0.5)) * i;
        rgb_ycc_tab[i +(5 *(255 + 1))] =((JLONG )(0.5 *(1L << 16) + 0.5)) * i +(((JLONG )128) << 16) +(((JLONG )1) << 16 - 1) - 1;
        rgb_ycc_tab[i +(6 *(255 + 1))] = -((JLONG )(0.41869 *(1L << 16) + 0.5)) * i;
        rgb_ycc_tab[i +(7 *(255 + 1))] = -((JLONG )(0.08131 *(1L << 16) + 0.5)) * i;
    }

#pragma endscop
}
