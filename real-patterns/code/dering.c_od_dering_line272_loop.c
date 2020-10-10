#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int sby;
extern int nvb;
extern int bsize;
extern int nvsb;
extern int j;
extern int sbx;
extern int nhb;
extern int nhsb;
typedef short int16_t;
extern int16_t * restrict in;
typedef int16_t od_dering_in;
extern od_dering_in * restrict x;
extern int xstride;

void loop()
{
#pragma scop

    for(i = - 3 *(sby != 0); i <(nvb << bsize) + 3 *(sby != nvsb - 1); i++)
    {
        for(j = - 3 *(sbx != 0); j <(nhb << bsize) + 3 *(sbx != nhsb - 1); j++)
        {
            in[i *((1 << 2 + 5 - 1) + 2 * 3) + j] = x[i * xstride + j];
        }
    }

#pragma endscop
}
