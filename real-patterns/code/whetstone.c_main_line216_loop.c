#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern long I;
extern long N4;
extern int J;

void loop()
{
#pragma scop

    for(I = 1; I <= N4; I++)
    {
        if(J == 1) J = 2;
        else J = 3;
        if(J > 2) J = 0;
        else J = 1;
        if(J < 1) J = 1;
        else J = 0;
    }

#pragma endscop
}
