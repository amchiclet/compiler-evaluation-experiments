#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int i;
extern int32_t  mdct_win[8][36] ;

void loop()
{
#pragma scop

    for(j = 0; j < 4; j++)
    {
        for(i = 0; i < 36; i += 2)
        {
            mdct_win[j + 4][i] = mdct_win[j][i];
            mdct_win[j + 4][i + 1] = -mdct_win[j][i + 1];
        }
    }

#pragma endscop
}
