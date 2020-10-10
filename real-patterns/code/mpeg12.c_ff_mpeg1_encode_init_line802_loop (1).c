#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int f_code;
extern int mv;
extern uint8_t  mbMotionVectorTable[17][2] ;
extern unsigned char (* restrict mv_penalty)[2048 * 2 + 1];
typedef unsigned char uint8_t;

void loop()
{
#pragma scop

    for(f_code = 1; f_code <= 7; f_code++)
    {
        for(mv = - 2048; mv <= 2048; mv++)
        {
            int len;
            if(mv == 0) len = mbMotionVectorTable[0][1];
            else
            {
                int val;
                int bit_size;
                int range;
                int code;
                bit_size = f_code - 1;
                range = 1 << bit_size;
                val = mv;
                if(val < 0) val = -val;
                val--;
                code =(val >> bit_size) + 1;
                if(code < 17)
                {
                    len = mbMotionVectorTable[code][1] + 1 + bit_size;
                }
                else
                {
                    len = mbMotionVectorTable[16][1] + 2 + bit_size;
                }
            }
            mv_penalty[f_code][mv + 2048] = len;
        }
    }

#pragma endscop
}
