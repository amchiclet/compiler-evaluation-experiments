#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000 - 5; i += 5)
    {
        a[i] = a[i + 1] * a[i];
        a[i + 1] = a[i + 2] * a[i + 1];
        a[i + 2] = a[i + 3] * a[i + 2];
        a[i + 3] = a[i + 4] * a[i + 3];
        a[i + 4] = a[i + 5] * a[i + 4];
    }

#pragma endscop
}
