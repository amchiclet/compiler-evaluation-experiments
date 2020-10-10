#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int dataSize;
extern int * restrict data1;
typedef long int64_t;
extern int gain_Q26;

void loop()
{
#pragma scop

    for(i = 0; i < dataSize; i++)
    {
        data1[i] =((int )(((int64_t )data1[i]) * gain_Q26 >> 8));
    }

#pragma endscop
}
