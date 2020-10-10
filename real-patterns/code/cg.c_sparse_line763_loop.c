#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int j;
extern int nrows;
extern int nzrow;
extern int k;
extern int jajp1;
extern int* restrict rowstr;
extern int i;
extern int* restrict colidx;
extern double* restrict x;
extern double* restrict a;
typedef int boolean;
extern int* restrict mark;
extern int* restrict nzloc;
extern double xi;
extern int nza;

void loop()
{
#pragma scop

    for(j = 1; j <= nrows; j++)
    {
        nzrow = 0;
        for(k = jajp1; k < rowstr[j + 1]; k++)
        {
            i = colidx[k];
            x[i] = x[i] + a[k];
            if(mark[i] == 0 && x[i] != 0.0)
            {
                mark[i] = 1;
                nzrow = nzrow + 1;
                nzloc[nzrow] = i;
            }
        }
        for(k = 1; k <= nzrow; k++)
        {
            i = nzloc[k];
            mark[i] = 0;
            xi = x[i];
            x[i] = 0.0;
            if(xi != 0.0)
            {
                nza = nza + 1;
                a[nza] = xi;
                colidx[nza] = i;
            }
        }
        jajp1 = rowstr[j + 1];
        rowstr[j + 1] = nza + rowstr[1];
    }

#pragma endscop
}
