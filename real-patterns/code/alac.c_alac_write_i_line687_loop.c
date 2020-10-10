#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int writecount;
extern int * restrict iptr;
extern int * restrict ptr;

void loop()
{
#pragma scop

    for(k = 0; k < writecount; k++) iptr[k] = ptr[k];

#pragma endscop
}
