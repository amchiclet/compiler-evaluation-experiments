#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int num_blocks;
extern int * restrict bdone;

void loop()
{
#pragma scop

    for(i = 0; i < num_blocks; i++) bdone[i] = 0;

#pragma endscop
}
