#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern unsigned int i;
extern unsigned int size;
extern unsigned int * restrict rot;

void loop()
{
#pragma scop

    for(i = 0; i < size; i++) rot[i] = i;

#pragma endscop
}
