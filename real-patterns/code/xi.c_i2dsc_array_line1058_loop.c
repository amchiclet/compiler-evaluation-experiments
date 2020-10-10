#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int count;
extern signed char current;
extern int * restrict src;
extern signed char * restrict dest;
extern signed char last_val;

void loop()
{
#pragma scop

    for(k = 0; k < count; k++)
    {
        current =(src[k] >> 24);
        dest[k] =(current - last_val);
        last_val = current;
    }

#pragma endscop
}
