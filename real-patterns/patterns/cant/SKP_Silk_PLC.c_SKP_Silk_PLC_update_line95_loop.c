#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int temp_LTP_Gain_Q14;
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
extern int j;

void loop()
{
#pragma scop

    for(i = 0; i < 5; i++)
    {
        temp_LTP_Gain_Q14 += psDecCtrl -> LTPCoef_Q14[(4 - 1 - j) * 5 + i];
    }

#pragma endscop
}
