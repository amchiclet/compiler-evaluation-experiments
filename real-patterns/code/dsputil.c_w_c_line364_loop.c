#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int h;
extern int j;
extern int w;
extern int s;
extern int  tmp[16 * 16] ;

void loop()
{
#pragma scop

    for(i = 0; i < h; i++)
    {
        for(j = 0; j < w; j += 4)
        {
            s +=(tmp[16 * i + j + 0] >= 0?tmp[16 * i + j + 0] : -tmp[16 * i + j + 0]);
            s +=(tmp[16 * i + j + 1] >= 0?tmp[16 * i + j + 1] : -tmp[16 * i + j + 1]);
            s +=(tmp[16 * i + j + 2] >= 0?tmp[16 * i + j + 2] : -tmp[16 * i + j + 2]);
            s +=(tmp[16 * i + j + 3] >= 0?tmp[16 * i + j + 3] : -tmp[16 * i + j + 3]);
        }
    }

#pragma endscop
}
