declare mt[];

for [mti] {
  mt[mti] = 1812433253 * (mt[mti - 1] ^ mt[mti - 1] >> 30) + mti;
  mt[mti] = mt[mti] & 0xffffffff;
}
