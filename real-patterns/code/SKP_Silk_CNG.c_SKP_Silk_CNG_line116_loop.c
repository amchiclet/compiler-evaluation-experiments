#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct
{
    int CNG_exc_buf_Q10[20 * 24];
    int CNG_smth_NLSF_Q15[16];
    int CNG_synth_state[16];
    int CNG_smth_Gain_Q16;
    int rand_seed;
    int fs_kHz;
} SKP_Silk_CNG_struct;
extern SKP_Silk_CNG_struct * restrict psCNG;
typedef struct
{
    int pitchL[4];
    int Gains_Q16[4];
    int Seed;
    short PredCoef_Q12[2][16];
    short LTPCoef_Q14[5 * 4];
    int LTP_scale_Q14;
    int PERIndex;
    int RateLevelIndex;
    int QuantOffsetType;
    int sigtype;
    int NLSFInterpCoef_Q2;
} SKP_Silk_decoder_control;
extern SKP_Silk_decoder_control * restrict psDecCtrl;

void loop()
{
#pragma scop

    for(i = 0; i < 4; i++)
    {
        psCNG -> CNG_smth_Gain_Q16 +=(psDecCtrl -> Gains_Q16[i] - psCNG -> CNG_smth_Gain_Q16 >> 16) *((int )((short )4634)) +((psDecCtrl -> Gains_Q16[i] - psCNG -> CNG_smth_Gain_Q16 & 0x0000FFFF) *((int )((short )4634)) >> 16);
    }

#pragma endscop
}
