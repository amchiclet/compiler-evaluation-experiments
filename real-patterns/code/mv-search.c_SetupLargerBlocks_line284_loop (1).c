#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int pos;
extern int max_pos;
extern int * restrict _o;
extern int * restrict _i;
extern int * restrict _j;

void loop()
{
#pragma scop

    for(pos = 0; pos < max_pos; pos++) _o[pos] = _i[pos] + _j[pos];

#pragma endscop
}
