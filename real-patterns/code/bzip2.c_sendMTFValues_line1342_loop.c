#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int t;
extern int v;
extern int alphaSize;
extern unsigned char  len[6][258] ;

void loop()
{
#pragma scop

    for(t = 0; t < 6; t++) for(v = 0; v < alphaSize; v++) len[t][v] = 15;

#pragma endscop
}
