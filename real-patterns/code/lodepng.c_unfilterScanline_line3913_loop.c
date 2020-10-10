#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned long size_t;
extern size_t i;
extern size_t bytewidth;
extern size_t length;
extern unsigned char * restrict recon;
extern unsigned char * restrict scanline;
extern unsigned char * restrict precon;

void loop()
{
#pragma scop

    for(i = bytewidth; i < length; ++i) recon[i] =(scanline[i] +(recon[i - bytewidth] + precon[i]) / 2);

#pragma endscop
}
