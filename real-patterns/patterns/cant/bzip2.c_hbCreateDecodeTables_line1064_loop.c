#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int minLen;
extern int maxLen;
extern int j;
extern int alphaSize;
extern unsigned char * restrict length;
extern int * restrict perm;
extern int pp;

void loop()
{
#pragma scop

    for(i = minLen; i <= maxLen; i++) for(j = 0; j < alphaSize; j++) if(length[j] == i)
            {
                perm[pp] = j;
                pp++;
            }

#pragma endscop
}
