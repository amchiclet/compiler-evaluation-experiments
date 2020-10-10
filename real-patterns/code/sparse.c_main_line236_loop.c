#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long long s64Int;
extern s64Int row;
extern s64Int size2;
extern double * restrict vector;

void loop()
{
#pragma scop

    for(row = 0; row < size2; row++) vector[row] +=((double )(row + 1));

#pragma endscop
}
