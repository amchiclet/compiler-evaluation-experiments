#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int kk;
extern int kmin;
extern int kmax;
extern int jj;
extern int jmin;
extern int jmax;
extern int ii;
extern int imin;
extern int imax;
extern int i;
extern int jp;
extern int kp;
extern double * restrict b;
extern double * restrict dbl;
extern double * restrict xdbl;
extern double * restrict dbc;
extern double * restrict xdbc;
extern double * restrict dbr;
extern double * restrict xdbr;
extern double * restrict dcl;
extern double * restrict xdcl;
extern double * restrict dcc;
extern double * restrict xdcc;
extern double * restrict dcr;
extern double * restrict xdcr;
extern double * restrict dfl;
extern double * restrict xdfl;
extern double * restrict dfc;
extern double * restrict xdfc;
extern double * restrict dfr;
extern double * restrict xdfr;
extern double * restrict cbl;
extern double * restrict xcbl;
extern double * restrict cbc;
extern double * restrict xcbc;
extern double * restrict cbr;
extern double * restrict xcbr;
extern double * restrict ccl;
extern double * restrict xccl;
extern double * restrict ccc;
extern double * restrict xccc;
extern double * restrict ccr;
extern double * restrict xccr;
extern double * restrict cfl;
extern double * restrict xcfl;
extern double * restrict cfc;
extern double * restrict xcfc;
extern double * restrict cfr;
extern double * restrict xcfr;
extern double * restrict ubl;
extern double * restrict xubl;
extern double * restrict ubc;
extern double * restrict xubc;
extern double * restrict ubr;
extern double * restrict xubr;
extern double * restrict ucl;
extern double * restrict xucl;
extern double * restrict ucc;
extern double * restrict xucc;
extern double * restrict ucr;
extern double * restrict xucr;
extern double * restrict ufl;
extern double * restrict xufl;
extern double * restrict ufc;
extern double * restrict xufc;
extern double * restrict ufr;
extern double * restrict xufr;

void loop()
{
#pragma scop

    for(kk = kmin; kk < kmax; kk++)
    {
        for(jj = jmin; jj < jmax; jj++)
        {
            for(ii = imin; ii < imax; ii++)
            {
                i = ii + jj * jp + kk * kp;
                b[i] = dbl[i] * xdbl[i] + dbc[i] * xdbc[i] + dbr[i] * xdbr[i] + dcl[i] * xdcl[i] + dcc[i] * xdcc[i] + dcr[i] * xdcr[i] + dfl[i] * xdfl[i] + dfc[i] * xdfc[i] + dfr[i] * xdfr[i] + cbl[i] * xcbl[i] + cbc[i] * xcbc[i] + cbr[i] * xcbr[i] + ccl[i] * xccl[i] + ccc[i] * xccc[i] + ccr[i] * xccr[i] + cfl[i] * xcfl[i] + cfc[i] * xcfc[i] + cfr[i] * xcfr[i] + ubl[i] * xubl[i] + ubc[i] * xubc[i] + ubr[i] * xubr[i] + ucl[i] * xucl[i] + ucc[i] * xucc[i] + ucr[i] * xucr[i] + ufl[i] * xufl[i] + ufc[i] * xufc[i] + ufr[i] * xufr[i];
            }
        }
    }

#pragma endscop
}
