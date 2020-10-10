#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int k;
extern int i;
extern int end1;
extern int address;
typedef short int16_t;
extern int16_t  psd[256] ;
extern int v;
typedef unsigned char uint8_t;
extern uint8_t * restrict bap;
extern uint8_t  baptab[64] ;

void loop()
{
#pragma scop

    for(k = i; k < end1; k++)
    {
        address = psd[i] - v >> 5;
        if(address < 0) address = 0;
        else if(address > 63) address = 63;
        bap[i] = baptab[address];
        i++;
    }

#pragma endscop
}
