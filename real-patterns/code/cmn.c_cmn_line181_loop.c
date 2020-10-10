#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
typedef int int32;
extern int32 f;
extern int32 n_frame;
typedef float float32;
typedef float32 mfcc_t;
extern mfcc_t * restrict mfcp;
extern mfcc_t ** restrict mfc;
extern int32 i;
typedef struct
{
    mfcc_t *cmn_mean;
    mfcc_t *cmn_var;
    mfcc_t *sum;
    int32 nframe;
    int32 veclen;
} cmn_t;
extern cmn_t * restrict cmn;

void loop()
{
#pragma scop

    for(f = 0; f < n_frame; f++)
    {
        mfcp = mfc[f];
        for(i = 0; i < cmn -> veclen; i++) mfcp[i] -= cmn -> cmn_mean[i];
    }

#pragma endscop
}
