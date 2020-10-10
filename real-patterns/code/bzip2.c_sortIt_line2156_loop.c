#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int * restrict ftab;

void loop()
{
#pragma scop

    for(i = 0; i <= 65536; i++) ftab[i] = 0;

#pragma endscop
}
