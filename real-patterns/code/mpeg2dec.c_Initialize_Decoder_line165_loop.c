#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern unsigned char * restrict Clip;

void loop()
{
#pragma scop

    for(i = - 384; i < 640; i++) Clip[i] =((i < 0?0 :((i > 255?255 : i))));

#pragma endscop
}
