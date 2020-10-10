#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
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
extern int max_Gain_Q16;
extern int subfr;

void loop()
{
#pragma scop

    for(i = 0; i < 4; i++)
    {
        if(psDecCtrl -> Gains_Q16[i] > max_Gain_Q16)
        {
            max_Gain_Q16 = psDecCtrl -> Gains_Q16[i];
            subfr = i;
        }
    }

#pragma endscop
}
