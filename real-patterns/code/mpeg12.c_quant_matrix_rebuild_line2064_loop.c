#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned short uint16_t;
extern uint16_t * restrict matrix;
extern uint8_t * restrict new_perm;
extern uint16_t  temp_matrix[64] ;
extern uint8_t * restrict old_perm;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i++)
    {
        matrix[new_perm[i]] = temp_matrix[old_perm[i]];
    }

#pragma endscop
}
