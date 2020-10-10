#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int v;
extern unsigned char  scale_diff_table[128] ;

void loop()
{
#pragma scop

    for(i = 0; i < 128; i++)
    {
        v = i - 64;
        if(v <= - 3) v = 0;
        else if(v < 0) v = 1;
        else if(v == 0) v = 2;
        else if(v < 3) v = 3;
        else v = 4;
        scale_diff_table[i] = v;
    }

#pragma endscop
}
