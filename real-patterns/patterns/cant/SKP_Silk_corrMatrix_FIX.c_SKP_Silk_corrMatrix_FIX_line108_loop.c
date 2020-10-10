declare energy;
declare XX[];
declare ptr1[];

for [j] {
  energy = energy - (ptr1[L - j] * ptr1[L - j] >> rshifts_local);
  energy = energy + (ptr1[-j] * ptr1[-j] >> rshifts_local);
  XX[j * order + j] = energy;
}
