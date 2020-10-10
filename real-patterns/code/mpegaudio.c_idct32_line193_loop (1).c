#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int * restrict tab;

void loop()
{
#pragma scop

    for(j = 31; j >= 3; j -= 2) tab[j] += tab[j - 2];

#pragma endscop
}
