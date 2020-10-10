#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int datalen;
extern unsigned char * restrict data;
typedef struct
{
    int le_float;
    int be_float;
    int le_int_24_32;
    int be_int_24_32;
} VOTE;
extern VOTE * restrict vote;

void loop()
{
#pragma scop

    for(k = 0; k < datalen; k++)
    {
        if(k % 4 == 0)
        {
            if(data[k] == 0 && data[k + 1] != 0) vote -> le_int_24_32 += 4;
            if(data[2] != 0 && data[3] == 0) vote -> le_int_24_32 += 4;
            if(data[0] != 0 && data[3] > 0x43 && data[3] < 0x4B) vote -> le_float += 4;
            if(data[3] != 0 && data[0] > 0x43 && data[0] < 0x4B) vote -> be_float += 4;
        };
    }

#pragma endscop
}
