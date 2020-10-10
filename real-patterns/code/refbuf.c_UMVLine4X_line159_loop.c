#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int xx;
extern int x;
extern int xpos;
extern int width4;
extern unsigned short  line4[64] ;
extern unsigned short ** restrict Pic;
extern int ypos;

void loop()
{
#pragma scop

    for(i = 0; i < 64; i += 4)
    {
        xx = x + i;
        xpos =(xx < 0?xx & 3 :((xx > width4?width4 +(xx & 3) : xx)));
        line4[i] = Pic[ypos][xpos];
    }

#pragma endscop
}
