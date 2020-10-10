#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nb_groups;
extern int exp_min;
typedef unsigned char uint8_t;
extern uint8_t  exp[(1 << 9) / 2] ;
extern int k;
extern int j;
extern int group_size;
extern uint8_t  exp1[512 / 2] ;

void loop()
{
#pragma scop

    for(i = 1; i <= nb_groups; i++)
    {
        exp_min = exp[k];
        (void )0;
        for(j = 1; j < group_size; j++)
        {
            if(exp[k + j] < exp_min) exp_min = exp[k + j];
        }
        exp1[i] = exp_min;
        k += group_size;
    }

#pragma endscop
}
