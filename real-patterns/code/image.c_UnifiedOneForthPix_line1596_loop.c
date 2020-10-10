#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int ie2;
extern int ii;
extern int i1;
extern int j;
extern int je2;
extern unsigned short ** restrict out4Y;

void loop()
{
#pragma scop

    for(i = 0; i < ie2 + 2; i++)
    {
        ii =(ie2 < i + 1?ie2 : i + 1);
        i1 = i - 1;
        for(j = 0; j < je2 - 2; j += 2)
        {
            if((i & 0x1) == 0)
            {
                out4Y[j + 1][i] =(out4Y[j][i] + out4Y[j + 2][i] + 1 >> 1);
            }
            else if((j & 0x3) == 0 &&(i & 0x3) == 1 ||(j & 0x3) == 2 &&(i & 0x3) == 3)
            {
                out4Y[j + 1][i] =(out4Y[j][ii] + out4Y[j + 2][i1] + 1 >> 1);
            }
            else
            {
                out4Y[j + 1][i] =(out4Y[j][i1] + out4Y[j + 2][ii] + 1 >> 1);
            }
        }
        for(j = je2 - 2; j < je2 + 1; j += 2)
        {
            if((i & 0x1) == 0)
            {
                out4Y[j + 1][i] =(out4Y[j][i] + out4Y[(je2 < j + 2?je2 : j + 2)][i] + 1 >> 1);
            }
            else if((j & 0x3) == 0 &&(i & 0x3) == 1 ||(j & 0x3) == 2 &&(i & 0x3) == 3)
            {
                out4Y[j + 1][i] =(out4Y[j][ii] + out4Y[(je2 < j + 2?je2 : j + 2)][i1] + 1 >> 1);
            }
            else
            {
                out4Y[j + 1][i] =((unsigned short )(((int )(out4Y[j][i1] + out4Y[(je2 < j + 2?je2 : j + 2)][ii] + 1)) >> 1));
            }
        }
    }

#pragma endscop
}
