#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int begin_bytepos;
extern int end_bytepos;
extern int count;
typedef unsigned char byte;
extern byte * restrict NAL_Payload_buffer;
extern byte * restrict streamBuffer;
extern int j;

void loop()
{
#pragma scop

    for(i = begin_bytepos; i < end_bytepos; i++)
    {
        if(count == 2 && !(NAL_Payload_buffer[i] & 0xFC))
        {
            streamBuffer[j] = 0x03;
            j++;
            count = 0;
        }
        streamBuffer[j] = NAL_Payload_buffer[i];
        if(NAL_Payload_buffer[i] == 0) count++;
        else count = 0;
        j++;
    }

#pragma endscop
}
