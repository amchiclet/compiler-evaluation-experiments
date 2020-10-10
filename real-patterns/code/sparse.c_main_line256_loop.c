#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long long s64Int;
extern s64Int row;
extern s64Int size2;
extern double vector_sum;
extern double * restrict result;

void loop()
{
#pragma scop

    for(row = 0; row < size2; row++) vector_sum += result[row];

#pragma endscop
}
