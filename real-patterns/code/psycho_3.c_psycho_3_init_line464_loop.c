#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int  numlines[513] ;
extern double  cbval[513] ;

void loop()
{
#pragma scop

    for(i = 1; i < 64; i++)
    {
        if(numlines[i] != 0) cbval[i] /= numlines[i];
        else
        {
            cbval[i] = 0;
        }
    }

#pragma endscop
}
