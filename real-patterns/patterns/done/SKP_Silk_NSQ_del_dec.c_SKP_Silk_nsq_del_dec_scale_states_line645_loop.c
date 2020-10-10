declare sLTP_shp_Q10[];
declare gain_adj_Q16;

# comment comment
for [i] {
  sLTP_shp_Q10[i] = (gain_adj_Q16 >> 16) * sLTP_shp_Q10[i] +
                    ((gain_adj_Q16 & 0x0000FFFF) * sLTP_shp_Q10[i] >> 16) +
		    gain_adj_Q16 * ((16 == 1 ?
				     (sLTP_shp_Q10[i] >> 1) + (sLTP_shp_Q10[i] & 1) :
				     (sLTP_shp_Q10[i] >> 16 - 1) + 1 >> 1)); 
}
