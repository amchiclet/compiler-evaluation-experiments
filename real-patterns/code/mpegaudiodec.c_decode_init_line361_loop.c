#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int x;
extern int xsize;
extern int y;
typedef unsigned char uint8_t;
extern uint8_t * restrict code_table;
extern int j;

void loop()
{
#pragma scop

    for(x = 0; x < xsize; x++)
    {
        for(y = 0; y < xsize; y++) code_table[j++] =(x << 4 | y);
    }

#pragma endscop
}
