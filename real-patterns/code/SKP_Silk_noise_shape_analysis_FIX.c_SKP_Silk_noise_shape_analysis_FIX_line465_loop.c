#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef struct
{
    int LastGainIndex;
    int HarmBoost_smth_Q16;
    int HarmShapeGain_smth_Q16;
    int Tilt_smth_Q16;
} SKP_Silk_shape_state_FIX;
extern SKP_Silk_shape_state_FIX * restrict psShapeSt;
extern int HarmBoost_Q16;
typedef long int64_t;
extern int HarmShapeGain_Q16;
extern int Tilt_Q16;
typedef struct
{
    int lagIndex;
    int contourIndex;
    int PERIndex;
    int LTPIndex[4];
    int NLSFIndices[10];
    int NLSFInterpCoef_Q2;
    int GainsIndices[4];
    int Seed;
    int LTP_scaleIndex;
    int RateLevelIndex;
    int QuantOffsetType;
    int sigtype;
    int pitchL[4];
    int LBRR_usage;
} SKP_Silk_encoder_control;
typedef struct
{
    SKP_Silk_encoder_control sCmn;
    int Gains_Q16[4];
    short PredCoef_Q12[2][16];
    short LTPCoef_Q14[5 * 4];
    int LTP_scale_Q14;
    short AR1_Q13[4 * 16];
    short AR2_Q13[4 * 16];
    int LF_shp_Q14[4];
    int GainsPre_Q14[4];
    int HarmBoost_Q14[4];
    int Tilt_Q14[4];
    int HarmShapeGain_Q14[4];
    int Lambda_Q10;
    int input_quality_Q14;
    int coding_quality_Q14;
    int pitch_freq_low_Hz;
    int current_SNR_dB_Q7;
    int sparseness_Q8;
    int predGain_Q16;
    int LTPredCodGain_Q7;
    int input_quality_bands_Q15[4];
    int input_tilt_Q15;
    int ResNrg[4];
    int ResNrgQ[4];
} SKP_Silk_encoder_control_FIX;
extern SKP_Silk_encoder_control_FIX * restrict psEncCtrl;

void loop()
{
#pragma scop

    for(k = 0; k < 4; k++)
    {
        psShapeSt -> HarmBoost_smth_Q16 = psShapeSt -> HarmBoost_smth_Q16 +((HarmBoost_Q16 - psShapeSt -> HarmBoost_smth_Q16 >> 16) *((int )((short )((int )((0.4f *(((int64_t )1) << 16)) + 0.5)))) +((HarmBoost_Q16 - psShapeSt -> HarmBoost_smth_Q16 & 0x0000FFFF) *((int )((short )((int )((0.4f *(((int64_t )1) << 16)) + 0.5)))) >> 16));
        psShapeSt -> HarmShapeGain_smth_Q16 = psShapeSt -> HarmShapeGain_smth_Q16 +((HarmShapeGain_Q16 - psShapeSt -> HarmShapeGain_smth_Q16 >> 16) *((int )((short )((int )((0.4f *(((int64_t )1) << 16)) + 0.5)))) +((HarmShapeGain_Q16 - psShapeSt -> HarmShapeGain_smth_Q16 & 0x0000FFFF) *((int )((short )((int )((0.4f *(((int64_t )1) << 16)) + 0.5)))) >> 16));
        psShapeSt -> Tilt_smth_Q16 = psShapeSt -> Tilt_smth_Q16 +((Tilt_Q16 - psShapeSt -> Tilt_smth_Q16 >> 16) *((int )((short )((int )((0.4f *(((int64_t )1) << 16)) + 0.5)))) +((Tilt_Q16 - psShapeSt -> Tilt_smth_Q16 & 0x0000FFFF) *((int )((short )((int )((0.4f *(((int64_t )1) << 16)) + 0.5)))) >> 16));
        psEncCtrl -> HarmBoost_Q14[k] =((int )((2 == 1?(psShapeSt -> HarmBoost_smth_Q16 >> 1) +(psShapeSt -> HarmBoost_smth_Q16 & 1) :(psShapeSt -> HarmBoost_smth_Q16 >> 2 - 1) + 1 >> 1)));
        psEncCtrl -> HarmShapeGain_Q14[k] =((int )((2 == 1?(psShapeSt -> HarmShapeGain_smth_Q16 >> 1) +(psShapeSt -> HarmShapeGain_smth_Q16 & 1) :(psShapeSt -> HarmShapeGain_smth_Q16 >> 2 - 1) + 1 >> 1)));
        psEncCtrl -> Tilt_Q14[k] =((int )((2 == 1?(psShapeSt -> Tilt_smth_Q16 >> 1) +(psShapeSt -> Tilt_smth_Q16 & 1) :(psShapeSt -> Tilt_smth_Q16 >> 2 - 1) + 1 >> 1)));
    }

#pragma endscop
}
