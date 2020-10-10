#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int l;
extern int * restrict perm;
extern int * restrict start;
extern int * restrict data_label;

void loop()
{
#pragma scop

    for(i = 0; i < l; i++)
    {
        perm[start[data_label[i]]] = i;
        ++start[data_label[i]];
    }

#pragma endscop
}
