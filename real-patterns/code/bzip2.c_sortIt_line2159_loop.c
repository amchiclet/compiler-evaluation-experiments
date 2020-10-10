#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int last;
extern unsigned char c2;
extern unsigned char * restrict block;
extern int * restrict ftab;
extern unsigned char c1;

void loop()
{
#pragma scop

    for(i = 0; i <= last; i++)
    {
        c2 = block[i];
        ftab[(c1 << 8) + c2]++;
        c1 = c2;
    }

#pragma endscop
}
