#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
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
extern int gain_add_Q16;
typedef struct
{
    int bufferLength;
    int bufferIx;
    unsigned int base_Q32;
    unsigned int range_Q16;
    int error;
    unsigned char buffer[1024];
} SKP_Silk_range_coder_state;
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
typedef struct
{
    int In_LP_State[2];
    int transition_frame_no;
    int mode;
} SKP_Silk_LP_state;
typedef struct
{
    int AnaState[2];
    int AnaState1[2];
    int AnaState2[2];
    int XnrgSubfr[4];
    int NrgRatioSmth_Q8[4];
    short HPstate;
    int NL[4];
    int inv_NL[4];
    int NoiseLevelBias[4];
    int counter;
} SKP_Silk_VAD_state;
typedef struct
{
    const int nVectors;
    const short *CB_NLSF_Q15;
    const short *Rates_Q5;
} SKP_Silk_NLSF_CBS;
typedef struct
{
    const int nStages;
    const SKP_Silk_NLSF_CBS *CBStages;
    const int *NDeltaMin_Q15;
    const unsigned short *CDF;
    const unsigned short *const *StartPtr;
    const int *MiddleIx;
} SKP_Silk_NLSF_CB_struct;
typedef struct
{
    unsigned char payload[1024];
    int nBytes;
    int usage;
} SKP_SILK_LBRR_struct;
struct _SKP_Silk_resampler_state_struct
{
    int sIIR[6];
    int sFIR[16];
    int sDown2[2];
    int batchSize;
    int invRatio_Q16;
    int FIR_Fracs;
    int input2x;
    const short *Coefs;
    int sDownPre[2];
    int sUpPost[2];
    int batchSizePrePost;
    int ratio_Q16;
    int nPreDownsamplers;
    int nPostUpsamplers;
    int magic_number;
};

typedef struct _SKP_Silk_resampler_state_struct SKP_Silk_resampler_state_struct;
typedef struct
{
    int S_HP_8_kHz[3][2];
    int ConsecSmplsAboveThres;
    int ActiveSpeech_ms;
    int SWB_detected;
    int WB_detected;
} SKP_Silk_detect_SWB_state;
typedef struct
{
    SKP_Silk_range_coder_state sRC;
    SKP_Silk_range_coder_state sRC_LBRR;
    SKP_Silk_nsq_state sNSQ;
    SKP_Silk_nsq_state sNSQ_LBRR;
    int In_HP_State[2];
    SKP_Silk_LP_state sLP;
    SKP_Silk_VAD_state sVAD;
    int LBRRprevLastGainIndex;
    int prev_sigtype;
    int typeOffsetPrev;
    int prevLag;
    int prev_lagIndex;
    int API_fs_Hz;
    int prev_API_fs_Hz;
    int maxInternal_fs_kHz;
    int fs_kHz;
    int fs_kHz_changed;
    int frame_length;
    int subfr_length;
    int la_pitch;
    int la_shape;
    int shapeWinLength;
    int TargetRate_bps;
    int PacketSize_ms;
    int PacketLoss_perc;
    int frameCounter;
    int Complexity;
    int nStatesDelayedDecision;
    int useInterpolatedNLSFs;
    int shapingLPCOrder;
    int predictLPCOrder;
    int pitchEstimationComplexity;
    int pitchEstimationLPCOrder;
    int pitchEstimationThreshold_Q16;
    int LTPQuantLowComplexity;
    int NLSF_MSVQ_Survivors;
    int first_frame_after_reset;
    int controlled_since_last_payload;
    int warping_Q16;
    short inputBuf[20 * 24];
    int inputBufIx;
    int nFramesInPayloadBuf;
    int nBytesInPayloadBuf;
    int frames_since_onset;
    const SKP_Silk_NLSF_CB_struct *psNLSF_CB[2];
    SKP_SILK_LBRR_struct LBRR_buffer[2];
    int oldest_LBRR_idx;
    int useInBandFEC;
    int LBRR_enabled;
    int LBRR_GainIncreases;
    int bitrateDiff;
    int bitrate_threshold_up;
    int bitrate_threshold_down;
    SKP_Silk_resampler_state_struct resampler_state;
    int noSpeechCounter;
    int useDTX;
    int inDTX;
    int vadFlag;
    SKP_Silk_detect_SWB_state sSWBdetect;
    signed char q[20 * 24];
    signed char q_LBRR[20 * 24];
} SKP_Silk_encoder_state;
typedef struct
{
    int LastGainIndex;
    int HarmBoost_smth_Q16;
    int HarmShapeGain_smth_Q16;
    int Tilt_smth_Q16;
} SKP_Silk_shape_state_FIX;
typedef struct
{
    short sLTP_shp[512];
    int sAR_shp[16 + 1];
    int sLTP_shp_buf_idx;
    int sLF_AR_shp_Q12;
    int sLF_MA_shp_Q12;
    int sHarmHP;
    int rand_seed;
    int lagPrev;
} SKP_Silk_prefilter_state_FIX;
typedef struct
{
    int pitch_LPC_win_length;
    int min_pitch_lag;
    int max_pitch_lag;
    int prev_NLSFq_Q15[16];
} SKP_Silk_predict_state_FIX;
typedef struct
{
    SKP_Silk_encoder_state sCmn;
    int variable_HP_smth1_Q15;
    int variable_HP_smth2_Q15;
    SKP_Silk_shape_state_FIX sShape;
    SKP_Silk_prefilter_state_FIX sPrefilt;
    SKP_Silk_predict_state_FIX sPred;
    short x_buf[2 *(20 * 24) + 5 * 24];
    int LTPCorr_Q15;
    int mu_LTP_Q8;
    int SNR_dB_Q7;
    int avgGain_Q16;
    int avgGain_Q16_one_bit_per_sample;
    int BufferedInChannel_ms;
    int speech_activity_Q8;
    int prevLTPredCodGain_Q7;
    int HPLTPredCodGain_Q7;
    int inBandFEC_SNR_comp_Q8;
} SKP_Silk_encoder_state_FIX;
extern SKP_Silk_encoder_state_FIX * restrict psEnc;
typedef long int64_t;

void loop()
{
#pragma scop

    for(k = 0; k < 4; k++)
    {
        psEncCtrl -> Gains_Q16[k] =((psEncCtrl -> Gains_Q16[k] + gain_add_Q16) & 0x80000000?0x7FFFFFFF : psEncCtrl -> Gains_Q16[k] + gain_add_Q16);
        psEnc -> avgGain_Q16 =(((psEnc -> avgGain_Q16 +((psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 >> 16) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) +((psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 & 0x0000FFFF) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) >> 16))) & 0x80000000) == 0?((((psEnc -> avgGain_Q16 &(psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 >> 16) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) +((psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 & 0x0000FFFF) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) >> 16)) & 0x80000000) != 0?((int )0x80000000) : psEnc -> avgGain_Q16 +((psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 >> 16) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) +((psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 & 0x0000FFFF) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) >> 16)))) :((((psEnc -> avgGain_Q16 |(psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 >> 16) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) +((psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 & 0x0000FFFF) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) >> 16)) & 0x80000000) == 0?0x7FFFFFFF : psEnc -> avgGain_Q16 +((psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 >> 16) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) +((psEncCtrl -> Gains_Q16[k] - psEnc -> avgGain_Q16 & 0x0000FFFF) *((int )((short )((2 == 1?(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 1) +(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) & 1) :(((int )((short )(psEnc -> speech_activity_Q8))) *((int )((short )((int )((1e-3f *(((int64_t )1) << 10)) + 0.5)))) >> 2 - 1) + 1 >> 1)))) >> 16)))));
    }

#pragma endscop
}
