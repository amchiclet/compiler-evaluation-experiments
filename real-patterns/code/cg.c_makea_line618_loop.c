#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int n;
extern int* restrict colidx;

void loop()
{
#pragma scop

    for(i = 1; i <= n; i++)
    {
        colidx[n + i] = 0;
    }

#pragma endscop
}
