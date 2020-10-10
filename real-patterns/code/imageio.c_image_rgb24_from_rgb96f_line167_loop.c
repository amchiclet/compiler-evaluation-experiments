#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int yres;
extern int x;
extern int xres;
extern int R;
extern float * restrict fimg;
extern int G;
extern int B;
extern unsigned char * restrict img;
typedef unsigned char byte;

void loop()
{
#pragma scop

    for(y = 0; y < yres; y++)
    {
        for(x = 0; x < xres; x++)
        {
            int addr =(xres * y + x) * 3;
            R =((int )(fimg[addr] * 255.0f));
            G =((int )(fimg[addr + 1] * 255.0f));
            B =((int )(fimg[addr + 2] * 255.0f));
            if(R > 255) R = 255;
            if(R < 0) R = 0;
            img[addr] =((byte )R);
            if(G > 255) G = 255;
            if(G < 0) G = 0;
            img[addr + 1] =((byte )G);
            if(B > 255) B = 255;
            if(B < 0) B = 0;
            img[addr + 2] =((byte )B);
        }
    }

#pragma endscop
}
