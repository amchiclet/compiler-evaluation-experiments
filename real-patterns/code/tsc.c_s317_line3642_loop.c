#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float q;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 / 2; i++)
    {
        q *=((float ).99);
    }

#pragma endscop
}
