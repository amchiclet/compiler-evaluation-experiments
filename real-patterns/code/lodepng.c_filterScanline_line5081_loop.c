#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long size_t;
extern size_t i;
extern size_t bytewidth;
extern size_t length;
extern unsigned char * restrict out;
extern unsigned char * restrict scanline;

void loop()
{
#pragma scop

    for(i = bytewidth; i < length; ++i) out[i] =(scanline[i] - scanline[i - bytewidth] / 2);

#pragma endscop
}
