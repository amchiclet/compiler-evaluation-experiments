#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ARCHnodes;
extern int * restrict nodekind;
extern double * restrict nodekindf;

void loop()
{
#pragma scop

    for(i = 0; i < ARCHnodes; i++)
    {
        nodekind[i] =((int )nodekindf[i]);
        if(nodekind[i] == 3) nodekind[i] = 1;
    }

#pragma endscop
}
