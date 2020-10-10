#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ctr;
typedef long int_fast16_t;
extern int_fast16_t tmp0;
typedef short DCTELEM;
extern DCTELEM * restrict dataptr;
extern int_fast16_t tmp7;
extern int_fast16_t tmp1;
extern int_fast16_t tmp6;
extern int_fast16_t tmp2;
extern int_fast16_t tmp5;
extern int_fast16_t tmp3;
extern int_fast16_t tmp4;
extern int_fast16_t tmp10;
extern int_fast16_t tmp13;
extern int_fast16_t tmp11;
extern int_fast16_t tmp12;
extern int_fast16_t z1;
typedef int int32_t;
extern int_fast16_t z5;
extern int_fast16_t z2;
extern int_fast16_t z4;
extern int_fast16_t z3;
extern int_fast16_t z11;
extern int_fast16_t z13;

void loop()
{
#pragma scop

    for(ctr = 8 - 1; ctr >= 0; ctr--)
    {
        tmp0 =(dataptr[8 * 0] + dataptr[8 * 7]);
        tmp7 =(dataptr[8 * 0] - dataptr[8 * 7]);
        tmp1 =(dataptr[8 * 1] + dataptr[8 * 6]);
        tmp6 =(dataptr[8 * 1] - dataptr[8 * 6]);
        tmp2 =(dataptr[8 * 2] + dataptr[8 * 5]);
        tmp5 =(dataptr[8 * 2] - dataptr[8 * 5]);
        tmp3 =(dataptr[8 * 3] + dataptr[8 * 4]);
        tmp4 =(dataptr[8 * 3] - dataptr[8 * 4]);
        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;
        dataptr[8 * 0] =(tmp10 + tmp11);
        dataptr[8 * 4] =(tmp10 - tmp11);
        z1 =((DCTELEM )((tmp12 + tmp13) *((int32_t )181) >> 8));
        dataptr[8 * 2] =(tmp13 + z1);
        dataptr[8 * 6] =(tmp13 - z1);
        tmp10 = tmp4 + tmp5;
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;
        z5 =((DCTELEM )((tmp10 - tmp12) *((int32_t )98) >> 8));
        z2 =((DCTELEM )(tmp10 *((int32_t )139) >> 8)) + z5;
        z4 =((DCTELEM )(tmp12 *((int32_t )334) >> 8)) + z5;
        z3 =((DCTELEM )(tmp11 *((int32_t )181) >> 8));
        z11 = tmp7 + z3;
        z13 = tmp7 - z3;
        dataptr[8 * 5] =(z13 + z2);
        dataptr[8 * 3] =(z13 - z2);
        dataptr[8 * 1] =(z11 + z4);
        dataptr[8 * 7] =(z11 - z4);
        dataptr++;
    }

#pragma endscop
}
