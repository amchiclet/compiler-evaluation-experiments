#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern float  a[32000] ;
extern float alpha;
extern float  b[32000] ;
extern int * __restrict__ restrict ip;

void loop()
{
#pragma scop

    for(int i = 0; i < 32000; i += 5)
    {
        a[i] += alpha * b[ip[i]];
        a[i + 1] += alpha * b[ip[i + 1]];
        a[i + 2] += alpha * b[ip[i + 2]];
        a[i + 3] += alpha * b[ip[i + 3]];
        a[i + 4] += alpha * b[ip[i + 4]];
    }

#pragma endscop
}
