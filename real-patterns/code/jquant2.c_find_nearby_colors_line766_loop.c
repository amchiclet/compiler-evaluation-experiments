#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int numcolors;
typedef long INT32;
extern INT32  mindist[255 + 1] ;
extern INT32 minmaxdist;
typedef unsigned char JSAMPLE;
extern unsigned char* restrict colorlist;
extern int ncolors;

void loop()
{
#pragma scop

    for(i = 0; i < numcolors; i++)
    {
        if(mindist[i] <= minmaxdist) colorlist[ncolors++] =((JSAMPLE )i);
    }

#pragma endscop
}
