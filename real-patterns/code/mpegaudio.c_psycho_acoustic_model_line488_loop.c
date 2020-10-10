#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
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
typedef long int64_t;
struct MpegAudioContext
{
    PutBitContext pb;
    int nb_channels;
    int freq;
    int bit_rate;
    int lsf;
    int bitrate_index;
    int freq_index;
    int frame_size;
    int64_t nb_samples;
    int frame_frac;
    int frame_frac_incr;
    int do_padding;
    short samples_buf[2][4096];
    int samples_offset[2];
    int sb_samples[2][3][12][32];
    unsigned char scale_factors[2][32][3];
    unsigned char scale_code[2][32];
    int sblimit;
    const unsigned char *alloc_table;
};

typedef struct MpegAudioContext  MpegAudioContext;
extern MpegAudioContext * restrict s;
extern short  smr[32] ;
extern float  fixed_smr[32] ;

void loop()
{
#pragma scop

    for(i = 0; i < s -> sblimit; i++)
    {
        smr[i] =((int )(fixed_smr[i] * 10));
    }

#pragma endscop
}
