#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int num_rr_nodes;
extern int num_inputs;
extern int * restrict num_inputs_to_cblock;
extern float trans_count;
extern float * restrict trans_per_cblock;

void loop()
{
#pragma scop

    for(i = 0; i < num_rr_nodes; i++)
    {
        num_inputs = num_inputs_to_cblock[i];
        trans_count += trans_per_cblock[num_inputs];
    }

#pragma endscop
}
