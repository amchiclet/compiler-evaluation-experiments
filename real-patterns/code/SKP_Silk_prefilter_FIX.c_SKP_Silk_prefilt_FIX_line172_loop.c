#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int length;
extern int lag;
extern int idx;
extern int LTP_shp_buf_idx;
extern int n_LTP_Q12;
extern short * restrict LTP_shp_buf;
extern int HarmShapeFIRPacked_Q12;
extern int n_Tilt_Q10;
extern int sLF_AR_shp_Q12;
extern int Tilt_Q14;
extern int n_LF_Q10;
extern int LF_shp_Q14;
extern int sLF_MA_shp_Q12;
extern int* restrict st_res_Q12;
extern short* restrict xw;

void loop()
{
#pragma scop

    for(i = 0; i < length; i++)
    {
        if(lag > 0)
        {
            ;
            idx = lag + LTP_shp_buf_idx;
            n_LTP_Q12 =((int )((short )LTP_shp_buf[idx - 3 / 2 - 1 & 512 - 1])) *((int )((short )HarmShapeFIRPacked_Q12));
            n_LTP_Q12 = n_LTP_Q12 +((int )((short )LTP_shp_buf[idx - 3 / 2 & 512 - 1])) *(HarmShapeFIRPacked_Q12 >> 16);
            n_LTP_Q12 = n_LTP_Q12 +((int )((short )LTP_shp_buf[idx - 3 / 2 + 1 & 512 - 1])) *((int )((short )HarmShapeFIRPacked_Q12));
        }
        else
        {
            n_LTP_Q12 = 0;
        }
        n_Tilt_Q10 =(sLF_AR_shp_Q12 >> 16) *((int )((short )Tilt_Q14)) +((sLF_AR_shp_Q12 & 0x0000FFFF) *((int )((short )Tilt_Q14)) >> 16);
        n_LF_Q10 =(sLF_AR_shp_Q12 >> 16) *(LF_shp_Q14 >> 16) +((sLF_AR_shp_Q12 & 0x0000FFFF) *(LF_shp_Q14 >> 16) >> 16) +((sLF_MA_shp_Q12 >> 16) *((int )((short )LF_shp_Q14)) +((sLF_MA_shp_Q12 & 0x0000FFFF) *((int )((short )LF_shp_Q14)) >> 16));
        sLF_AR_shp_Q12 = st_res_Q12[i] -(n_Tilt_Q10 << 2);
        sLF_MA_shp_Q12 = sLF_AR_shp_Q12 -(n_LF_Q10 << 2);
        LTP_shp_buf_idx = LTP_shp_buf_idx - 1 & 512 - 1;
        LTP_shp_buf[LTP_shp_buf_idx] =((short )((((12 == 1?(sLF_MA_shp_Q12 >> 1) +(sLF_MA_shp_Q12 & 1) :(sLF_MA_shp_Q12 >> 12 - 1) + 1 >> 1)) > 0x7FFF?0x7FFF :((((12 == 1?(sLF_MA_shp_Q12 >> 1) +(sLF_MA_shp_Q12 & 1) :(sLF_MA_shp_Q12 >> 12 - 1) + 1 >> 1)) <((short )0x8000)?((short )0x8000) :((12 == 1?(sLF_MA_shp_Q12 >> 1) +(sLF_MA_shp_Q12 & 1) :(sLF_MA_shp_Q12 >> 12 - 1) + 1 >> 1)))))));
        xw[i] =((short )((((12 == 1?(sLF_MA_shp_Q12 - n_LTP_Q12 >> 1) +(sLF_MA_shp_Q12 - n_LTP_Q12 & 1) :(sLF_MA_shp_Q12 - n_LTP_Q12 >> 12 - 1) + 1 >> 1)) > 0x7FFF?0x7FFF :((((12 == 1?(sLF_MA_shp_Q12 - n_LTP_Q12 >> 1) +(sLF_MA_shp_Q12 - n_LTP_Q12 & 1) :(sLF_MA_shp_Q12 - n_LTP_Q12 >> 12 - 1) + 1 >> 1)) <((short )0x8000)?((short )0x8000) :((12 == 1?(sLF_MA_shp_Q12 - n_LTP_Q12 >> 1) +(sLF_MA_shp_Q12 - n_LTP_Q12 & 1) :(sLF_MA_shp_Q12 - n_LTP_Q12 >> 12 - 1) + 1 >> 1)))))));
    }

#pragma endscop
}
