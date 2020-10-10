#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int * restrict numlines;
extern double * restrict cbval;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        if(numlines[i] != 0) cbval[i] /= numlines[i];
        else
        {
            cbval[i] = 0;
        }
    }

#pragma endscop
}
