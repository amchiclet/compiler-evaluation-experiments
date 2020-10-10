#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int by;
extern int nvb;
extern int bx;
extern int nhb;
extern int xdec;
extern int overlap;
extern int sbx;
extern int sby;
extern int nhsb;
extern int nvsb;
extern int i;
extern int j;
extern unsigned char * restrict bskip;
extern int skip_stride;
extern int  thresh[64 / 8][64 / 8] ;

void loop()
{
#pragma scop

    for(by = 0; by < nvb; by++)
    {
        for(bx = 0; bx < nhb; bx++)
        {
            int skip;
            int xstart;
            int ystart;
            int xend;
            int yend;
            xstart = ystart = 0;
            xend = yend = 2 >> xdec;
            if(overlap)
            {
                xstart -= sbx != 0;
                ystart -= sby != 0;
                xend += sbx != nhsb - 1;
                yend += sby != nvsb - 1;
            }
            skip = 1;
            for(i = ystart; i < yend; i++)
            {
                for(j = xstart; j < xend; j++)
                {
                    skip = skip && bskip[((by << 1 >> xdec) + i) * skip_stride +(bx << 1 >> xdec) + j];
                }
            }
            if(skip) thresh[by][bx] = 0;
        }
    }

#pragma endscop
}
