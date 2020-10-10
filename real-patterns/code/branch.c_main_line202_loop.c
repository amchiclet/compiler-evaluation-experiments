#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern long vector_length;
extern int * restrict vector;
extern int * restrict index;

void loop()
{
#pragma scop

    for(i = 0; i < vector_length; i++)
    {
        vector[i] = 3 -(i & 7);
        index[i] = i;
    }

#pragma endscop
}
