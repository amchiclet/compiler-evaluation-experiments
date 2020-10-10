#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int len;
extern int * restrict out;
extern int * restrict in;

void loop()
{
#pragma scop

    for(k = 0; k < len; k++)
    {
        out[k] = in[2 * k] + in[2 * k + 1];
    }

#pragma endscop
}
