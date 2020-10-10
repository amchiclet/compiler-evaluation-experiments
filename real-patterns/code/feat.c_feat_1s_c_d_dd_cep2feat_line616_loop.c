#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int int32;
extern int32 i;
typedef unsigned int uint32;
typedef float float32;
typedef float32 mfcc_t;
enum cmn_type_e {CMN_NONE=0,CMN_CURRENT=1,CMN_PRIOR=2};;
typedef enum cmn_type_e cmn_type_t;
enum agc_type_e {AGC_NONE=0,AGC_MAX=1,AGC_EMAX=2,AGC_NOISE=3};;
typedef enum agc_type_e agc_type_t;
typedef struct
{
    mfcc_t *cmn_mean;
    mfcc_t *cmn_var;
    mfcc_t *sum;
    int32 nframe;
    int32 veclen;
} cmn_t;
struct agc_s
{
    mfcc_t max;
    mfcc_t obs_max;
    int32 obs_frame;
    int32 obs_utt;
    mfcc_t obs_max_sum;
    mfcc_t noise_thresh;
};

typedef struct agc_s  agc_t;
struct feat_s
{
    int refcount;
    char *name;
    int32 cepsize;
    int32 n_stream;
    uint32 *stream_len;
    int32 window_size;
    int32 n_sv;
    uint32 *sv_len;
    int32 **subvecs;
    mfcc_t *sv_buf;
    int32 sv_dim;
    cmn_type_t cmn;
    int32 varnorm;
    agc_type_t agc;
    cmn_t *cmn_struct;
    agc_t *agc_struct;
    mfcc_t **cepbuf;
    mfcc_t **tmpcepbuf;
    int32 bufpos;
    int32 curpos;
    mfcc_t ***lda;
    uint32 n_lda;
    uint32 out_dim;
};

typedef struct feat_s  feat_t;
extern feat_t * restrict fcb;
extern mfcc_t d1;
extern mfcc_t * restrict w1;
extern mfcc_t * restrict _w1;
extern mfcc_t d2;
extern mfcc_t * restrict w_1;
extern mfcc_t * restrict _w_1;
extern mfcc_t * restrict f;

void loop()
{
#pragma scop

    for(i = 0; i < fcb -> cepsize; i++)
    {
        d1 = w1[i] - _w1[i];
        d2 = w_1[i] - _w_1[i];
        f[i] = d1 - d2;
    }

#pragma endscop
}
