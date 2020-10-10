#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct
{
    short xq[2 *(20 * 24)];
    int sLTP_shp_Q10[2 *(20 * 24)];
    int sLPC_Q14[20 * 24 / 4 + 32];
    int sAR2_Q14[16];
    int sLF_AR_shp_Q12;
    int lagPrev;
    int sLTP_buf_idx;
    int sLTP_shp_buf_idx;
    int rand_seed;
    int prev_inv_gain_Q16;
    int rewhite_flag;
} SKP_Silk_nsq_state;
extern SKP_Silk_nsq_state * restrict NSQ;
extern int lag;
extern int* restrict sLTP_Q16;
extern int gain_adj_Q16;

void loop()
{
#pragma scop

    for(i = NSQ -> sLTP_buf_idx - lag - 5 / 2; i < NSQ -> sLTP_buf_idx; i++)
    {
        sLTP_Q16[i] =(gain_adj_Q16 >> 16) *((int )((short )sLTP_Q16[i])) +((gain_adj_Q16 & 0x0000FFFF) *((int )((short )sLTP_Q16[i])) >> 16) + gain_adj_Q16 *((16 == 1?(sLTP_Q16[i] >> 1) +(sLTP_Q16[i] & 1) :(sLTP_Q16[i] >> 16 - 1) + 1 >> 1));
    }

#pragma endscop
}
