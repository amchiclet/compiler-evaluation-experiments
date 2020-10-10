#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int mv;
typedef unsigned char uint8_t;
extern uint8_t  umv_fcode_tab[2048 * 2 + 1] ;

void loop()
{
#pragma scop

    for(mv = 0; mv < 2048 * 2 + 1; mv++)
    {
        umv_fcode_tab[mv] = 1;
    }

#pragma endscop
}
