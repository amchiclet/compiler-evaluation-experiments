#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int j;
extern int  codesize[257] ;
typedef unsigned char UINT8;
typedef int boolean;
typedef struct
{
    UINT8 bits[17];
    UINT8 huffval[256];
    boolean sent_table;
} JHUFF_TBL;
extern JHUFF_TBL * restrict htbl;
extern int p;

void loop()
{
#pragma scop

    for(i = 1; i <= 32; i++)
    {
        for(j = 0; j <= 255; j++)
        {
            if(codesize[j] == i)
            {
                htbl -> huffval[p] =((UINT8 )j);
                p++;
            }
        }
    }

#pragma endscop
}
