#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int y_off;
extern int y_pos;
extern int pels;
extern int i;
extern int MB_mean;
extern unsigned char * restrict curr;
extern int x_pos;

void loop()
{
#pragma scop

    for(j = 0; j < 16; j++)
    {
        y_off =(y_pos + j) * pels;
        for(i = 0; i < 16; i++)
        {
            MB_mean +=( *(curr + x_pos + i + y_off));
        }
    }

#pragma endscop
}
