#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int nb_coefs;
extern int mant;
typedef unsigned char uint8_t;
extern uint8_t * restrict m;
typedef unsigned int uint32_t;
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
extern int bits;

void loop()
{
#pragma scop

    for(i = 0; i < nb_coefs; i++)
    {
        mant = m[i];
        switch(mant)
        {
        case 0:
            break;
        case 1:
        {
            if(s -> mant1_cnt == 0) bits += 5;
            if(++s -> mant1_cnt == 3) s -> mant1_cnt = 0;
            break;
        }
        case 2:
        {
            if(s -> mant2_cnt == 0) bits += 7;
            if(++s -> mant2_cnt == 3) s -> mant2_cnt = 0;
            break;
        }
        case 3:
        {
            bits += 3;
            break;
        }
        case 4:
        {
            if(s -> mant4_cnt == 0) bits += 7;
            if(++s -> mant4_cnt == 2) s -> mant4_cnt = 0;
            break;
        }
        case 14:
        {
            bits += 14;
            break;
        }
        case 15:
        {
            bits += 16;
            break;
        }
        default:
        {
            bits += mant - 1;
            break;
        }
        }
    }

#pragma endscop
}
