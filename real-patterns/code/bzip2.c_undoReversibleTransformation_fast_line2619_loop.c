#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int last;
extern unsigned char ch;
extern unsigned char * restrict ll8;
extern int * restrict tt;
extern int  cftab[257] ;

void loop()
{
#pragma scop

    for(i = 0; i <= last; i++)
    {
        ch =((unsigned char )ll8[i]);
        tt[cftab[ch]] = i;
        cftab[ch]++;
    }

#pragma endscop
}
