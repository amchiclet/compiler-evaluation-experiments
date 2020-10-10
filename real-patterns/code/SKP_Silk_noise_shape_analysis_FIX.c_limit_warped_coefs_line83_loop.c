#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int i;
extern int order;
extern int tmp;
extern int * restrict coefs_syn_Q24;
extern int * restrict coefs_ana_Q24;
extern int maxabs_Q24;
extern int ind;

void loop()
{
#pragma scop

    for(i = 0; i < order; i++)
    {
        tmp =((coefs_syn_Q24[i] ^ coefs_syn_Q24[i] >> 31) -(coefs_syn_Q24[i] >> 31) >(coefs_ana_Q24[i] ^ coefs_ana_Q24[i] >> 31) -(coefs_ana_Q24[i] >> 31)?(coefs_syn_Q24[i] ^ coefs_syn_Q24[i] >> 31) -(coefs_syn_Q24[i] >> 31) :(coefs_ana_Q24[i] ^ coefs_ana_Q24[i] >> 31) -(coefs_ana_Q24[i] >> 31));
        if(tmp > maxabs_Q24)
        {
            maxabs_Q24 = tmp;
            ind = i;
        }
    }

#pragma endscop
}
