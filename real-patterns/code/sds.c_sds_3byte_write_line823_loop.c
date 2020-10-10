#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern unsigned int sample;
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
extern unsigned char * restrict ucptr;

void loop()
{
#pragma scop

    for(k = 0; k < 120; k += 3)
    {
        sample = psds -> write_samples[k / 3];
        sample += 0x80000000;
        ucptr[k] =(sample >> 25 & 0x7F);
        ucptr[k + 1] =(sample >> 18 & 0x7F);
        ucptr[k + 2] =(sample >> 11 & 0x7F);
    }

#pragma endscop
}
