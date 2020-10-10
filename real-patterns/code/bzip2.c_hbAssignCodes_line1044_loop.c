#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int n;
extern int minLen;
extern int maxLen;
extern int i;
extern int alphaSize;
extern unsigned char * restrict length;
extern int * restrict code;
extern int vec;

void loop()
{
#pragma scop

    for(n = minLen; n <= maxLen; n++)
    {
        for(i = 0; i < alphaSize; i++) if(length[i] == n)
            {
                code[i] = vec;
                vec++;
            };
        vec <<= 1;
    }

#pragma endscop
}
