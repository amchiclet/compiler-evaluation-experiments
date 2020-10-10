#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
typedef unsigned char uint8_t;
struct RangeCoder
{
    int low;
    int range;
    int outstanding_count;
    int outstanding_byte;
    uint8_t zero_state[256];
    uint8_t one_state[256];
    uint8_t *bytestream_start;
    uint8_t *bytestream;
    uint8_t *bytestream_end;
};

typedef struct RangeCoder  RangeCoder;
extern RangeCoder * restrict c;

void loop()
{
#pragma scop

    for(i = 1; i < 255; i++) c -> zero_state[i] =(256 - c -> one_state[256 - i]);

#pragma endscop
}
