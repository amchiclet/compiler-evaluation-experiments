#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int writecount;
extern int * restrict iptr;
extern short * restrict ptr;
typedef long int64_t;
typedef int64_t sf_count_t;
extern sf_count_t total;

void loop()
{
#pragma scop

    for(k = 0; k < writecount; k++) iptr[k] = ptr[total + k] << 16;

#pragma endscop
}
