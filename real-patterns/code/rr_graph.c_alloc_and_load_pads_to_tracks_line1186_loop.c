#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
extern int ipad;
extern int io_rat;
extern int iconn;
extern int Fc_pad;
extern int itrack;
extern float step_size;
extern int nodes_per_chan;
extern int ** restrict pads_to_tracks;

void loop()
{
#pragma scop

    for(ipad = 0; ipad < io_rat; ipad++)
    {
        for(iconn = 0; iconn < Fc_pad; iconn++)
        {
            itrack =((int )(ipad * step_size + iconn *((float )nodes_per_chan) /((float )Fc_pad)));
            itrack =(itrack > nodes_per_chan - 1?nodes_per_chan - 1 : itrack);
            pads_to_tracks[ipad][iconn] = itrack;
        }
    }

#pragma endscop
}
