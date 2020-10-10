#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nb_groups;
typedef unsigned char uint8_t;
extern uint8_t  exp1[512 / 2] ;

void loop()
{
#pragma scop

    for(i = 1; i <= nb_groups; i++) exp1[i] =((exp1[i] > exp1[i - 1] + 2?exp1[i - 1] + 2 : exp1[i]));

#pragma endscop
}
