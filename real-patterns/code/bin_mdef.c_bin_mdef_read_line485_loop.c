#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int int32;
extern int32 i;
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
extern bin_mdef_t * restrict m;

void loop()
{
#pragma scop

    for(i = 0; i < m -> n_sen; ++i) m -> sen2cimap[i] =(- 1);

#pragma endscop
}
