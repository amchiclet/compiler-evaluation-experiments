#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int readcount;
extern short * restrict ptr;
typedef long int64_t;
typedef int64_t sf_count_t;
extern sf_count_t total;
extern int * restrict iptr;

void loop()
{
#pragma scop

    for(k = 0; k < readcount; k++) ptr[total + k] =(iptr[k] >> 16);

#pragma endscop
}
