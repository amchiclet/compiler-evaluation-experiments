#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ctr;
typedef long int_fast32_t;
extern int_fast32_t tmp0;
typedef short DCTELEM;
extern DCTELEM * restrict dataptr;
extern int_fast32_t tmp7;
extern int_fast32_t tmp1;
extern int_fast32_t tmp6;
extern int_fast32_t tmp2;
extern int_fast32_t tmp5;
extern int_fast32_t tmp3;
extern int_fast32_t tmp4;
extern int_fast32_t tmp10;
extern int_fast32_t tmp13;
extern int_fast32_t tmp11;
extern int_fast32_t tmp12;
extern int_fast32_t z1;
typedef int int32_t;
extern int_fast32_t z2;
extern int_fast32_t z3;
extern int_fast32_t z4;
extern int_fast32_t z5;

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
        dataptr[8 * 0] =((DCTELEM )(tmp10 + tmp11 +(1 << 4 - 1) >> 4));
        dataptr[8 * 4] =((DCTELEM )(tmp10 - tmp11 +(1 << 4 - 1) >> 4));
        z1 =(tmp12 + tmp13) *((int32_t )4433);
        dataptr[8 * 2] =((DCTELEM )(z1 + tmp13 *((int32_t )6270) +(1 << 13 + 4 - 1) >> 13 + 4));
        dataptr[8 * 6] =((DCTELEM )(z1 + tmp12 *(-((int32_t )15137)) +(1 << 13 + 4 - 1) >> 13 + 4));
        z1 = tmp4 + tmp7;
        z2 = tmp5 + tmp6;
        z3 = tmp4 + tmp6;
        z4 = tmp5 + tmp7;
        z5 =(z3 + z4) *((int32_t )9633);
        tmp4 = tmp4 *((int32_t )2446);
        tmp5 = tmp5 *((int32_t )16819);
        tmp6 = tmp6 *((int32_t )25172);
        tmp7 = tmp7 *((int32_t )12299);
        z1 = z1 *(-((int32_t )7373));
        z2 = z2 *(-((int32_t )20995));
        z3 = z3 *(-((int32_t )16069));
        z4 = z4 *(-((int32_t )3196));
        z3 += z5;
        z4 += z5;
        dataptr[8 * 7] =((DCTELEM )(tmp4 + z1 + z3 +(1 << 13 + 4 - 1) >> 13 + 4));
        dataptr[8 * 5] =((DCTELEM )(tmp5 + z2 + z4 +(1 << 13 + 4 - 1) >> 13 + 4));
        dataptr[8 * 3] =((DCTELEM )(tmp6 + z2 + z3 +(1 << 13 + 4 - 1) >> 13 + 4));
        dataptr[8 * 1] =((DCTELEM )(tmp7 + z1 + z4 +(1 << 13 + 4 - 1) >> 13 + 4));
        dataptr++;
    }

#pragma endscop
}
