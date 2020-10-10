#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ctr;
typedef unsigned char JSAMPLE;
typedef JSAMPLE * JSAMPROW;
extern JSAMPROW restrict outptr;
typedef JSAMPROW * JSAMPARRAY;
extern JSAMPARRAY restrict output_buf;
typedef unsigned int JDIMENSION;
extern JDIMENSION output_col;
extern int * restrict wsptr;
extern JSAMPLE * restrict range_limit;
typedef long INT32;
extern INT32 z2;
extern INT32 z3;
extern INT32 z1;
extern INT32 tmp2;
extern INT32 tmp3;
extern INT32 tmp0;
extern INT32 tmp1;
extern INT32 tmp10;
extern INT32 tmp13;
extern INT32 tmp11;
extern INT32 tmp12;
extern INT32 z4;
extern INT32 z5;

void loop()
{
#pragma scop

    for(ctr = 0; ctr < 8; ctr++)
    {
        outptr = output_buf[ctr] + output_col;
        if(wsptr[1] == 0 && wsptr[2] == 0 && wsptr[3] == 0 && wsptr[4] == 0 && wsptr[5] == 0 && wsptr[6] == 0 && wsptr[7] == 0)
        {
            JSAMPLE dcval = range_limit[((int )(((INT32 )wsptr[0]) +(((INT32 )1) << 2 + 3 - 1) >> 2 + 3)) & 255 * 4 + 3];
            outptr[0] = dcval;
            outptr[1] = dcval;
            outptr[2] = dcval;
            outptr[3] = dcval;
            outptr[4] = dcval;
            outptr[5] = dcval;
            outptr[6] = dcval;
            outptr[7] = dcval;
            wsptr += 8;
            continue;
        }
        z2 =((INT32 )wsptr[2]);
        z3 =((INT32 )wsptr[6]);
        z1 =(z2 + z3) *((INT32 )4433);
        tmp2 = z1 + z3 * -((INT32 )15137);
        tmp3 = z1 + z2 *((INT32 )6270);
        tmp0 =((INT32 )wsptr[0]) +((INT32 )wsptr[4]) << 13;
        tmp1 =((INT32 )wsptr[0]) -((INT32 )wsptr[4]) << 13;
        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;
        tmp0 =((INT32 )wsptr[7]);
        tmp1 =((INT32 )wsptr[5]);
        tmp2 =((INT32 )wsptr[3]);
        tmp3 =((INT32 )wsptr[1]);
        z1 = tmp0 + tmp3;
        z2 = tmp1 + tmp2;
        z3 = tmp0 + tmp2;
        z4 = tmp1 + tmp3;
        z5 =(z3 + z4) *((INT32 )9633);
        tmp0 = tmp0 *((INT32 )2446);
        tmp1 = tmp1 *((INT32 )16819);
        tmp2 = tmp2 *((INT32 )25172);
        tmp3 = tmp3 *((INT32 )12299);
        z1 = z1 * -((INT32 )7373);
        z2 = z2 * -((INT32 )20995);
        z3 = z3 * -((INT32 )16069);
        z4 = z4 * -((INT32 )3196);
        z3 += z5;
        z4 += z5;
        tmp0 += z1 + z3;
        tmp1 += z2 + z4;
        tmp2 += z2 + z3;
        tmp3 += z1 + z4;
        outptr[0] = range_limit[((int )(tmp10 + tmp3 +(((INT32 )1) << 13 + 2 + 3 - 1) >> 13 + 2 + 3)) & 255 * 4 + 3];
        outptr[7] = range_limit[((int )(tmp10 - tmp3 +(((INT32 )1) << 13 + 2 + 3 - 1) >> 13 + 2 + 3)) & 255 * 4 + 3];
        outptr[1] = range_limit[((int )(tmp11 + tmp2 +(((INT32 )1) << 13 + 2 + 3 - 1) >> 13 + 2 + 3)) & 255 * 4 + 3];
        outptr[6] = range_limit[((int )(tmp11 - tmp2 +(((INT32 )1) << 13 + 2 + 3 - 1) >> 13 + 2 + 3)) & 255 * 4 + 3];
        outptr[2] = range_limit[((int )(tmp12 + tmp1 +(((INT32 )1) << 13 + 2 + 3 - 1) >> 13 + 2 + 3)) & 255 * 4 + 3];
        outptr[5] = range_limit[((int )(tmp12 - tmp1 +(((INT32 )1) << 13 + 2 + 3 - 1) >> 13 + 2 + 3)) & 255 * 4 + 3];
        outptr[3] = range_limit[((int )(tmp13 + tmp0 +(((INT32 )1) << 13 + 2 + 3 - 1) >> 13 + 2 + 3)) & 255 * 4 + 3];
        outptr[4] = range_limit[((int )(tmp13 - tmp0 +(((INT32 )1) << 13 + 2 + 3 - 1) >> 13 + 2 + 3)) & 255 * 4 + 3];
        wsptr += 8;
    }

#pragma endscop
}
