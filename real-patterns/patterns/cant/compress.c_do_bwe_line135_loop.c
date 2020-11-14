#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern unsigned int i;
extern unsigned int size;
extern unsigned char * restrict bw;
extern unsigned char * restrict in;
extern unsigned int * restrict rot;

void loop()
{
#pragma scop

    for(i = 0; i < size; i++)
    {
        bw[i] = in[(rot[i] + size - 1) % size];
    }

#pragma endscop
}
