#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
typedef unsigned int uint32_t;
extern uint32_t sample;
extern unsigned char * restrict ucptr;
struct tag_SDS_PRIVATE
{
    int bitwidth;
    int frames;
    int samplesperblock;
    int total_blocks;
    int read_block;
    int read_count;
    unsigned char read_data[127];
    int read_samples[127 / 2];
    int write_block;
    int write_count;
    int total_written;
    unsigned char write_data[127];
    int write_samples[127 / 2];
};

typedef struct tag_SDS_PRIVATE SDS_PRIVATE;
extern SDS_PRIVATE * restrict psds;

void loop()
{
#pragma scop

    for(k = 0; k < 120; k += 4)
    {
        sample =(((uint32_t )ucptr[k]) << 25) +(ucptr[k + 1] << 18) +(ucptr[k + 2] << 11) +(ucptr[k + 3] << 4);
        psds -> read_samples[k / 4] =((int )(sample - 0x80000000));
    }

#pragma endscop
}
