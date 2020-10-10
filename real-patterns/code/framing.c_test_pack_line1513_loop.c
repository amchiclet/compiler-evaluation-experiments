#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int packets;
extern int packetskip;
extern long depacket;
extern int * restrict pl;

void loop()
{
#pragma scop

    for(packets = 0; packets < packetskip; packets++) depacket += pl[packets];

#pragma endscop
}
