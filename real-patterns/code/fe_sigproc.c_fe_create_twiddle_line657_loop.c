#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned long size_t;
struct hash_entry_s
{
    const char *key;
    size_t len;
    void *val;
    struct hash_entry_s *next;
};

typedef struct hash_entry_s  hash_entry_t;
typedef int int32;
typedef struct
{
    hash_entry_t *table;
    int32 size;
    int32 inuse;
    int32 nocase;
} hash_table_t;
typedef unsigned int uint32;
struct cmd_ln_s
{
    int refcount;
    hash_table_t *ht;
    char **f_argv;
    uint32 f_argc;
};

typedef struct cmd_ln_s cmd_ln_t;
typedef float float32;
typedef short int16;
typedef unsigned char uint8;
typedef double float64;
typedef float64 frame_t;
typedef float32 mfcc_t;
struct melfb_s
{
    float32 sampling_rate;
    int32 num_cepstra;
    int32 num_filters;
    int32 fft_size;
    float32 lower_filt_freq;
    float32 upper_filt_freq;
    mfcc_t **mel_cosine;
    mfcc_t *filt_coeffs;
    int16 *spec_start;
    int16 *filt_start;
    int16 *filt_width;
    int32 doublewide;
    const char *warp_type;
    const char *warp_params;
    uint32 warp_id;
    mfcc_t sqrt_inv_n;
    mfcc_t sqrt_inv_2n;
    int32 lifter_val;
    mfcc_t *lifter;
    int32 unit_area;
    int32 round_filters;
};

typedef struct melfb_s melfb_t;
typedef float64 window_t;
typedef float64 powspec_t;
struct fe_s
{
    cmd_ln_t *config;
    int refcount;
    float32 sampling_rate;
    int16 frame_rate;
    int16 frame_shift;
    float32 window_length;
    int16 frame_size;
    int16 fft_size;
    uint8 fft_order;
    uint8 feature_dimension;
    uint8 num_cepstra;
    uint8 remove_dc;
    uint8 log_spec;
    uint8 swap;
    uint8 dither;
    uint8 transform;
    float32 pre_emphasis_alpha;
    int32 seed;
    int16 frame_counter;
    uint8 start_flag;
    uint8 reserved;
    frame_t *ccc;
    frame_t *sss;
    melfb_t *mel_fb;
    window_t *hamming_window;
    int16 *spch;
    frame_t *frame;
    powspec_t *spec;
    powspec_t *mfspec;
    int16 *overflow_samps;
    int16 num_overflow_samps;
    int16 prior;
};

typedef struct fe_s fe_t;
extern fe_t * restrict fe;

void loop()
{
#pragma scop

    for(i = 0; i <(fe -> fft_size) / 4; ++i)
    {
        float64 a = 2 * 3.14159265358979323846 * i /(fe -> fft_size);
        fe -> ccc[i] = cos(a);
        fe -> sss[i] = sin(a);
    }

#pragma endscop
}
