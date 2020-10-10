#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern short * restrict iclp;

void loop()
{
#pragma scop

    for(i = - 512; i < 512; i++) iclp[i] =((i < - 256?- 256 :((i > 255?255 : i))));

#pragma endscop
}
