#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int int32;
extern int32 b;
extern int32 extra_bits;
typedef unsigned int uint32;
typedef uint32 bitvec_t;
extern bitvec_t * restrict flagptr;
extern int32 w;
extern int32 l;
union anytype_s
{
    void *ptr;
    long i;
    unsigned long ui;
    double fl;
};

typedef union anytype_s  anytype_t;
struct gnode_s
{
    anytype_t data;
    struct gnode_s *next;
};

typedef struct gnode_s  gnode_t;
typedef gnode_t * glist_t;
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
typedef short int16;
struct cd_tree_s
{
    int16 ctx;
    int16 n_down;
    union
    {
        int32 pid;
        int32 down;
    } c;
};

typedef struct cd_tree_s cd_tree_t;
typedef unsigned char uint8;
struct mdef_entry_s
{
    int32 ssid;
    int32 tmat;
    union
    {
        struct
        {
            uint8 filler;
            uint8 reserved[3];
        } ci;
        struct
        {
            uint8 wpos;
            uint8 ctx[3];
        } cd;
    } info;
} __attribute__((packed));

typedef struct mdef_entry_s mdef_entry_t;
typedef unsigned short uint16;
enum BIN_MDEF_FROM_TEXT_enum {BIN_MDEF_FROM_TEXT=0,BIN_MDEF_IN_MEMORY=1,BIN_MDEF_ON_DISK=2};;
struct bin_mdef_s
{
    int refcnt;
    int32 n_ciphone;
    int32 n_phone;
    int32 n_emit_state;
    int32 n_ci_sen;
    int32 n_sen;
    int32 n_tmat;
    int32 n_sseq;
    int32 n_ctx;
    int32 n_cd_tree;
    int16 sil;
    char **ciname;
    cd_tree_t *cd_tree;
    mdef_entry_t *phone;
    uint16 **sseq;
    uint8 *sseq_len;
    int16 *cd2cisen;
    int16 *sen2cimap;
};

typedef struct bin_mdef_s bin_mdef_t;
typedef struct
{
    uint8 ***tp;
    int16 n_tmat;
    int16 n_state;
} tmat_t;
struct ps_mgaufuncs_s
{
    const char *name;
};

typedef struct ps_mgaufuncs_s  ps_mgaufuncs_t;
struct ps_mgau_s
{
    ps_mgaufuncs_t *vt;
    int frame_idx;
};

typedef struct ps_mgau_s ps_mgau_t;
struct ps_mllr_s
{
    int refcnt;
    int n_class;
    int n_feat;
    int *veclen;
    float32 ****A;
    float32 ***b;
    float32 ***h;
    int32 *cb2mllr;
};

typedef struct ps_mllr_s ps_mllr_t;
typedef int16 frame_idx_t;
struct acmod_s
{
    glist_t strings;
    feat_t *fcb;
    bin_mdef_t *mdef;
    tmat_t *tmat;
    ps_mgau_t *mgau;
    ps_mllr_t *mllr;
    int16 *senone_scores;
    bitvec_t *senone_active_vec;
    uint8 *senone_active;
    int senscr_frame;
    int n_senone_active;
    int log_zero;
    mfcc_t **mfc_buf;
    mfcc_t ***feat_buf;
    FILE *rawfh;
    FILE *mfcfh;
    FILE *senfh;
    FILE *insenfh;
    long *framepos;
    uint8 state;
    uint8 compallsen;
    uint8 grow_feat;
    uint8 insen_swap;
    frame_idx_t output_frame;
    frame_idx_t n_mfc_alloc;
    frame_idx_t n_mfc_frame;
    frame_idx_t mfc_outidx;
    frame_idx_t n_feat_alloc;
    frame_idx_t n_feat_frame;
    frame_idx_t feat_outidx;
};

typedef struct acmod_s acmod_t;
extern acmod_t * restrict acmod;
extern int32 n;

void loop()
{
#pragma scop

    for(b = 0; b < extra_bits; ++b)
    {
        if(( *flagptr) & 1UL << b)
        {
            int32 sen = w * 32 + b;
            int32 delta = sen - l;
            while(delta > 255)
            {
                acmod -> senone_active[n++] = 255;
                delta -= 255;
            }
            acmod -> senone_active[n++] = delta;
            l = sen;
        }
    }

#pragma endscop
}
