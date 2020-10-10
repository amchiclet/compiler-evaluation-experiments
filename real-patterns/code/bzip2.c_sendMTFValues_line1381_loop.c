#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int v;
extern int alphaSize;
extern int gs;
extern int ge;
extern unsigned char  len[6][258] ;
extern int nPart;

void loop()
{
#pragma scop

    for(v = 0; v < alphaSize; v++) if(v >= gs && v <= ge) len[nPart - 1][v] = 0;
        else len[nPart - 1][v] = 15;

#pragma endscop
}
