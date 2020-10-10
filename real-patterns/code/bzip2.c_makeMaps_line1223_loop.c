#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern unsigned char  inUse[256] ;
extern unsigned char  seqToUnseq[256] ;
extern int nInUse;
extern unsigned char  unseqToSeq[256] ;

void loop()
{
#pragma scop

    for(i = 0; i < 256; i++) if(inUse[i])
        {
            seqToUnseq[nInUse] = i;
            unseqToSeq[i] = nInUse;
            nInUse++;
        }

#pragma endscop
}
