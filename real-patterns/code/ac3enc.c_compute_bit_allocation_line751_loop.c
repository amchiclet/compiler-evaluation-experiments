#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int frame_bits;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
struct PutBitContext
{
    uint32_t bit_buf;
    int bit_left;
    uint8_t *buf;
    uint8_t *buf_ptr;
    uint8_t *buf_end;
};

typedef struct PutBitContext  PutBitContext;
struct AC3BitAllocParameters
{
    int fscod;
    int halfratecod;
    int sgain;
    int sdecay;
    int fdecay;
    int dbknee;
    int floor;
    int cplfleak;
    int cplsleak;
};

typedef struct AC3BitAllocParameters  AC3BitAllocParameters;
struct AC3EncodeContext
{
    PutBitContext pb;
    int nb_channels;
    int nb_all_channels;
    int lfe_channel;
    int bit_rate;
    unsigned int sample_rate;
    unsigned int bsid;
    unsigned int frame_size_min;
    unsigned int frame_size;
    unsigned int bits_written;
    unsigned int samples_written;
    int halfratecod;
    unsigned int frmsizecod;
    unsigned int fscod;
    unsigned int acmod;
    int lfe;
    unsigned int bsmod;
    short last_samples[6][256];
    unsigned int chbwcod[6];
    int nb_coefs[6];
    int sgaincod;
    int sdecaycod;
    int fdecaycod;
    int dbkneecod;
    int floorcod;
    AC3BitAllocParameters bit_alloc;
    int csnroffst;
    int fgaincod[6];
    int fsnroffst[6];
    int mant1_cnt;
    int mant2_cnt;
    int mant4_cnt;
};

typedef struct AC3EncodeContext  AC3EncodeContext;
extern AC3EncodeContext * restrict s;
extern int ch;
extern uint8_t  exp_strategy[6][6] ;

void loop()
{
#pragma scop

    for(i = 0; i < 6; i++)
    {
        frame_bits += s -> nb_channels * 2 + 2;
        if(s -> acmod == 2)
        {
            frame_bits++;
            if(i == 0) frame_bits += 4;
        }
        frame_bits += 2 * s -> nb_channels;
        if(s -> lfe) frame_bits++;
        for(ch = 0; ch < s -> nb_channels; ch++)
        {
            if(exp_strategy[i][ch] != 0) frame_bits += 6 + 2;
        }
        frame_bits++;
        frame_bits++;
        frame_bits += 2;
    }

#pragma endscop
}
