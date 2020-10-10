#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int inemo;
extern int  nemo[8 * 2400] ;
extern int imor;
extern int ie;
extern int  emo[8 * 2400][8][2] ;
extern int sizei;
extern int  size_e[2400] ;
extern int cornernumber;
extern int sface;
extern int sedge;
extern int iiface;
extern int iface;
extern int  f_c[8][3] ;
extern int  cbc[2400][6] ;
extern int iiedge;
extern int iedge;
extern int  e_c[8][3] ;
enum false_enum{false=0, true=1};
typedef enum false_enum logical;
extern logical  ncon_edge[2400][12] ;
extern int n;
extern double tmortemp;
extern double  pcmor_cor[6][8] ;

void loop()
{
#pragma scop

    for(inemo = 0; inemo <= nemo[imor]; inemo++)
    {
        ie = emo[imor][inemo][0];
        sizei = size_e[ie];
        cornernumber = emo[imor][inemo][1];
        sface = 0;
        sedge = 0;
        for(iiface = 0; iiface < 3; iiface++)
        {
            iface = f_c[cornernumber][iiface];
            if(cbc[ie][iface] == 3)
            {
                sface = sface + 1;
            }
        }
        for(iiedge = 0; iiedge < 3; iiedge++)
        {
            iedge = e_c[cornernumber][iiedge];
            if(ncon_edge[ie][iedge]) sedge = sedge + 1;
        }
        if(sface == 0)
        {
            if(sedge == 0)
            {
                n = 7;
            }
            else if(sedge == 1)
            {
                n = 0;
            }
            else if(sedge == 2)
            {
                n = 1;
            }
            else if(sedge == 3)
            {
                n = 2;
            }
        }
        else if(sface == 1)
        {
            if(sedge == 1)
            {
                n = 4;
            }
            else
            {
                n = 3;
            }
        }
        else if(sface == 2)
        {
            n = 5;
        }
        else if(sface == 3)
        {
            n = 6;
        }
        tmortemp = tmortemp + pcmor_cor[sizei][n];
    }

#pragma endscop
}
