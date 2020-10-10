#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int last;
extern unsigned char  unseqToSeq[256] ;
extern unsigned char * restrict block;
extern int * restrict zptr;
extern int j;
extern unsigned char tmp;
extern unsigned char  yy[256] ;
extern unsigned char tmp2;
extern int zPend;
extern unsigned short * restrict szptr;
extern int wr;
extern int  mtfFreq[258] ;

void loop()
{
#pragma scop

    for(i = 0; i <= last; i++)
    {
        unsigned char ll_i;
        ll_i = unseqToSeq[block[zptr[i] - 1]];
        j = 0;
        tmp = yy[j];
        while(ll_i != tmp)
        {
            j++;
            tmp2 = tmp;
            tmp = yy[j];
            yy[j] = tmp2;
        };
        yy[0] = tmp;
        if(j == 0)
        {
            zPend++;
        }
        else
        {
            if(zPend > 0)
            {
                zPend--;
                while(1)
                {
                    switch(zPend % 2)
                    {
                    case 0:
                    {
                        szptr[wr] = 0;
                        wr++;
                        mtfFreq[0]++;
                        break;
                    }
                    case 1:
                    {
                        szptr[wr] = 1;
                        wr++;
                        mtfFreq[1]++;
                        break;
                    }
                    };
                    if(zPend < 2) break;
                    zPend =(zPend - 2) / 2;
                };
                zPend = 0;
            }
            szptr[wr] =(j + 1);
            wr++;
            mtfFreq[j + 1]++;
        }
    }

#pragma endscop
}
