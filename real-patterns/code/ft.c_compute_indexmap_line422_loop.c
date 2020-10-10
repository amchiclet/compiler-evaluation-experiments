#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern double  ex[6 *(256 * 256 / 4 + 256 * 256 / 4 + 128 * 128 / 4) + 1] ;

void loop()
{
#pragma scop

    for(i = 2; i <= 6 *(256 * 256 / 4 + 256 * 256 / 4 + 128 * 128 / 4); i++)
    {
        ex[i] = ex[i - 1] * ex[1];
    }

#pragma endscop
}
