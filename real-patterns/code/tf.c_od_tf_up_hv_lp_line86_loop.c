#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int y;
extern int n;
extern int x;
typedef int int32_t;
typedef int32_t od_coeff;
extern od_coeff * restrict src;
extern int sstride;
extern int dx;
extern int dy;
extern od_coeff * restrict dst;
extern int dstride;

void loop()
{
#pragma scop

    for(y = 0; y < n >> 1; y++)
    {
        int vswap;
        vswap = y & 1;
        for(x = 0; x < n >> 1; x++)
        {
            od_coeff ll;
            od_coeff lh;
            od_coeff hl;
            od_coeff hh;
            int hswap;
            ll = src[y * sstride + x];
            lh = src[y * sstride + x + dx];
            hl = src[(y + dy) * sstride + x];
            hh = src[(y + dy) * sstride + x + dx];
            do
            {
                od_coeff llmhh_2__;
                ll += lh;
                hh -= hl;
                llmhh_2__ = ll - hh >> 1;
                hl = llmhh_2__ - hl;
                lh = llmhh_2__ - lh;
                ll -= hl;
                hh += lh;
            }
            while(0);
            hswap = x & 1;
            dst[(2 * y + vswap) * dstride + 2 * x + hswap] = ll;
            dst[(2 * y + vswap) * dstride + 2 * x + 1 - hswap] = lh;
            dst[(2 * y + 1 - vswap) * dstride + 2 * x + hswap] = hl;
            dst[(2 * y + 1 - vswap) * dstride + 2 * x + 1 - hswap] = hh;
        }
    }

#pragma endscop
}
