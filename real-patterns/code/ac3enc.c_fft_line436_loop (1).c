#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nblocks;
struct IComplex
{
    short re;
    short im;
};

typedef struct IComplex  IComplex;
extern IComplex * restrict p;
extern IComplex * restrict q;
extern int l;
extern int np2;
extern int tmp_re;
typedef short int16_t;
extern int16_t  costab[64] ;
extern int16_t  sintab[64] ;
extern int tmp_im;
extern int nloops;

void loop()
{
#pragma scop

    for(j = 0; j < nblocks; ++j)
    {
        {
            int ax;
            int ay;
            int bx;
            int by;
            bx =(p -> re);
            by =(p -> im);
            ax =(q -> re);
            ay =(q -> im);
            p -> re =(bx + ax >> 1);
            p -> im =(by + ay >> 1);
            q -> re =(bx - ax >> 1);
            q -> im =(by - ay >> 1);
        };
        p++;
        q++;
        for(l = nblocks; l < np2; l += nblocks)
        {
            {
                tmp_re = costab[l] *(q -> re) - -sintab[l] *(q -> im) >> 15;
                tmp_im = costab[l] *(q -> im) +(q -> re) * -sintab[l] >> 15;
            };
            {
                int ax;
                int ay;
                int bx;
                int by;
                bx =(p -> re);
                by =(p -> im);
                ax = tmp_re;
                ay = tmp_im;
                p -> re =(bx + ax >> 1);
                p -> im =(by + ay >> 1);
                q -> re =(bx - ax >> 1);
                q -> im =(by - ay >> 1);
            };
            p++;
            q++;
        }
        p += nloops;
        q += nloops;
    }

#pragma endscop
}
