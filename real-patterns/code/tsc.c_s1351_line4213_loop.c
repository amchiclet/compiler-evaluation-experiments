#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float * restrict A;
extern float * restrict B;
extern float * restrict C;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i++)
    {
        *A = *B + *C;
        A++;
        B++;
        C++;
    }

#pragma endscop
}
