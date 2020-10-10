#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef long long s64Int;
extern s64Int elm;
extern s64Int row;
extern int stencil_size;
extern double * restrict matrix;
extern s64Int * restrict colIndex;

void loop()
{
#pragma scop

    for(elm = row * stencil_size; elm <(row + 1) * stencil_size; elm++) matrix[elm] = 1.0 /((double )(colIndex[elm] + 1));

#pragma endscop
}
