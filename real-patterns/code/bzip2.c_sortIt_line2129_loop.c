#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern unsigned char * restrict block;
extern int last;

void loop()
{
#pragma scop

    for(i = 0; i < 20; i++) block[last + i + 1] = block[i %(last + 1)];

#pragma endscop
}
