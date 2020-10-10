#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int f_code;
extern int mv;
typedef unsigned char uint8_t;
extern uint8_t  fcode_tab[2048 * 2 + 1] ;

void loop()
{
#pragma scop

    for(f_code = 7; f_code > 0; f_code--)
    {
        for(mv = -(8 << f_code); mv < 8 << f_code; mv++)
        {
            fcode_tab[mv + 2048] = f_code;
        }
    }

#pragma endscop
}
