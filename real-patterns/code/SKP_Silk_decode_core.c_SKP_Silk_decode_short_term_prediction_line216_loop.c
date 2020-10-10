#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int subfr_length;
extern int LPC_pred_Q10;
extern int * restrict sLPC_Q14;
extern short * restrict A_Q12_tmp;
extern int j;
extern int LPC_order;
extern int * restrict vec_Q10;
extern int * restrict pres_Q10;

void loop()
{
#pragma scop

    for(i = 0; i < subfr_length; i++)
    {
        LPC_pred_Q10 =(sLPC_Q14[16 + i - 1] >> 16) *((int )((short )A_Q12_tmp[0])) +((sLPC_Q14[16 + i - 1] & 0x0000FFFF) *((int )((short )A_Q12_tmp[0])) >> 16);
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 2] >> 16) *((int )((short )A_Q12_tmp[1])) +((sLPC_Q14[16 + i - 2] & 0x0000FFFF) *((int )((short )A_Q12_tmp[1])) >> 16));
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 3] >> 16) *((int )((short )A_Q12_tmp[2])) +((sLPC_Q14[16 + i - 3] & 0x0000FFFF) *((int )((short )A_Q12_tmp[2])) >> 16));
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 4] >> 16) *((int )((short )A_Q12_tmp[3])) +((sLPC_Q14[16 + i - 4] & 0x0000FFFF) *((int )((short )A_Q12_tmp[3])) >> 16));
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 5] >> 16) *((int )((short )A_Q12_tmp[4])) +((sLPC_Q14[16 + i - 5] & 0x0000FFFF) *((int )((short )A_Q12_tmp[4])) >> 16));
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 6] >> 16) *((int )((short )A_Q12_tmp[5])) +((sLPC_Q14[16 + i - 6] & 0x0000FFFF) *((int )((short )A_Q12_tmp[5])) >> 16));
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 7] >> 16) *((int )((short )A_Q12_tmp[6])) +((sLPC_Q14[16 + i - 7] & 0x0000FFFF) *((int )((short )A_Q12_tmp[6])) >> 16));
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 8] >> 16) *((int )((short )A_Q12_tmp[7])) +((sLPC_Q14[16 + i - 8] & 0x0000FFFF) *((int )((short )A_Q12_tmp[7])) >> 16));
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 9] >> 16) *((int )((short )A_Q12_tmp[8])) +((sLPC_Q14[16 + i - 9] & 0x0000FFFF) *((int )((short )A_Q12_tmp[8])) >> 16));
        LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - 10] >> 16) *((int )((short )A_Q12_tmp[9])) +((sLPC_Q14[16 + i - 10] & 0x0000FFFF) *((int )((short )A_Q12_tmp[9])) >> 16));
        for(j = 10; j < LPC_order; j++)
        {
            LPC_pred_Q10 = LPC_pred_Q10 +((sLPC_Q14[16 + i - j - 1] >> 16) *((int )((short )A_Q12_tmp[j])) +((sLPC_Q14[16 + i - j - 1] & 0x0000FFFF) *((int )((short )A_Q12_tmp[j])) >> 16));
        }
        vec_Q10[i] = pres_Q10[i] + LPC_pred_Q10;
        sLPC_Q14[16 + i] = vec_Q10[i] << 4;
    }

#pragma endscop
}
