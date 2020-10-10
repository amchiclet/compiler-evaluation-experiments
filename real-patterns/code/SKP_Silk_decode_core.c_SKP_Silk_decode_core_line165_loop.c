#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef struct
{
    int bufferLength;
    int bufferIx;
    unsigned int base_Q32;
    unsigned int range_Q16;
    int error;
    unsigned char buffer[1024];
} SKP_Silk_range_coder_state;
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
    int CNG_exc_buf_Q10[20 * 24];
    int CNG_smth_NLSF_Q15[16];
    int CNG_synth_state[16];
    int CNG_smth_Gain_Q16;
    int rand_seed;
    int fs_kHz;
} SKP_Silk_CNG_struct;
typedef struct
{
    int pitchL_Q8;
    short LTPCoef_Q14[5];
    short prevLPC_Q12[16];
    int last_frame_lost;
    int rand_seed;
    short randScale_Q14;
    int conc_energy;
    int conc_energy_shift;
    short prevLTP_scale_Q14;
    int prevGain_Q16[4];
    int fs_kHz;
} SKP_Silk_PLC_struct;
typedef struct
{
    SKP_Silk_range_coder_state sRC;
    int prev_inv_gain_Q16;
    int sLTP_Q16[2 *(20 * 24)];
    int sLPC_Q14[20 * 24 / 4 + 16];
    int exc_Q10[20 * 24];
    int res_Q10[20 * 24];
    short outBuf[2 *(20 * 24)];
    int lagPrev;
    int LastGainIndex;
    int LastGainIndex_EnhLayer;
    int typeOffsetPrev;
    int HPState[2];
    const short *HP_A;
    const short *HP_B;
    int fs_kHz;
    int prev_API_sampleRate;
    int frame_length;
    int subfr_length;
    int LPC_order;
    int prevNLSF_Q15[16];
    int first_frame_after_reset;
    int nBytesLeft;
    int nFramesDecoded;
    int nFramesInPacket;
    int moreInternalDecoderFrames;
    int FrameTermination;
    SKP_Silk_resampler_state_struct resampler_state;
    const SKP_Silk_NLSF_CB_struct *psNLSF_CB[2];
    int vadFlag;
    int no_FEC_counter;
    int inband_FEC_offset;
    SKP_Silk_CNG_struct sCNG;
    int lossCnt;
    int prev_sigtype;
    SKP_Silk_PLC_struct sPLC;
} SKP_Silk_decoder_state;
extern SKP_Silk_decoder_state * restrict psDec;
extern int LTP_pred_Q14;
extern int * restrict pred_lag_ptr;
extern short * restrict B_Q14;
extern int * restrict pres_Q10;
extern int * restrict pexc_Q10;
extern int sLTP_buf_idx;

void loop()
{
#pragma scop

    for(i = 0; i < psDec -> subfr_length; i++)
    {
        LTP_pred_Q14 =(pred_lag_ptr[0] >> 16) *((int )((short )B_Q14[0])) +((pred_lag_ptr[0] & 0x0000FFFF) *((int )((short )B_Q14[0])) >> 16);
        LTP_pred_Q14 = LTP_pred_Q14 +((pred_lag_ptr[- 1] >> 16) *((int )((short )B_Q14[1])) +((pred_lag_ptr[- 1] & 0x0000FFFF) *((int )((short )B_Q14[1])) >> 16));
        LTP_pred_Q14 = LTP_pred_Q14 +((pred_lag_ptr[- 2] >> 16) *((int )((short )B_Q14[2])) +((pred_lag_ptr[- 2] & 0x0000FFFF) *((int )((short )B_Q14[2])) >> 16));
        LTP_pred_Q14 = LTP_pred_Q14 +((pred_lag_ptr[- 3] >> 16) *((int )((short )B_Q14[3])) +((pred_lag_ptr[- 3] & 0x0000FFFF) *((int )((short )B_Q14[3])) >> 16));
        LTP_pred_Q14 = LTP_pred_Q14 +((pred_lag_ptr[- 4] >> 16) *((int )((short )B_Q14[4])) +((pred_lag_ptr[- 4] & 0x0000FFFF) *((int )((short )B_Q14[4])) >> 16));
        pred_lag_ptr++;
        pres_Q10[i] = pexc_Q10[i] +((4 == 1?(LTP_pred_Q14 >> 1) +(LTP_pred_Q14 & 1) :(LTP_pred_Q14 >> 4 - 1) + 1 >> 1));
        psDec -> sLTP_Q16[sLTP_buf_idx] = pres_Q10[i] << 6;
        sLTP_buf_idx++;
    }

#pragma endscop
}
