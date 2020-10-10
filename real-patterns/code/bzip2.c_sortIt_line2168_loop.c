#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int last;
extern unsigned char c2;
extern unsigned char * restrict block;
extern int j;
extern unsigned char c1;
extern int * restrict ftab;
extern int * restrict zptr;

void loop()
{
#pragma scop

    for(i = 0; i < last; i++)
    {
        c2 = block[i + 1];
        j =(c1 << 8) + c2;
        c1 = c2;
        ftab[j]--;
        zptr[ftab[j]] = i;
    }

#pragma endscop
}
