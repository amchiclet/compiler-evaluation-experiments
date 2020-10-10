declare tmp1_QS;
declare input[];
declare tmp2_QS;
declare state_QS[];
declare warping_Q16;
declare corr_QC[];

for [n] {
  tmp1_QS = input[n] << 14;
  for [(i, +=2)] {
      tmp2_QS =
	state_QS[i] + (
	  (state_QS[i + 1] - tmp1_QS >> 16) * warping_Q16 + (
	    (state_QS[i + 1] - tmp1_QS & 0x0000FFFF) * warping_Q16 >> 16
	  )
        );
      state_QS[i] = tmp1_QS;
      corr_QC[i] = corr_QC[i] + tmp1_QS * state_QS[0] >> 2 * 14 - 10;
      tmp1_QS =
	state_QS[i + 1] + (
	  (state_QS[i + 2] - tmp2_QS >> 16) * warping_Q16 + (
	    (state_QS[i + 2] - tmp2_QS & 0x0000FFFF) * warping_Q16 >> 16
	  )
	);
      state_QS[i + 1] = tmp2_QS;
      corr_QC[i + 1] = corr_QC[i + 1] + tmp2_QS * state_QS[0] >> 2 * 14 - 10;
  }
  state_QS[order] = tmp1_QS;
  corr_QC[order] = corr_QC[order] + tmp1_QS * state_QS[0] >> 2 * 14 - 10;
}
