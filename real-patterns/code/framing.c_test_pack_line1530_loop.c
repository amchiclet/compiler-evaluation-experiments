#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int len;
extern unsigned char * restrict data;
extern long inptr;
extern int i;

void loop()
{
#pragma scop

    for(j = 0; j < len; j++) data[inptr++] =(i + j);

#pragma endscop
}
