#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n1;
extern int n3;
extern float  a[32000] ;
extern float  b[32000] ;

void loop()
{
#pragma scop

    for(int i = n1 - 1; i < 32000; i += n3)
    {
        a[i] += b[i];
    }

#pragma endscop
}
