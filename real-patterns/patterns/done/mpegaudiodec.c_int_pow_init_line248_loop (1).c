declare a;
declare dev_4_3_coefs[];

for [i] {
  a = (a * ((4.0 / 3.0 * (1 << 24)) - i * (1.0 * (1 << 24))) >> 24) / (i + 1);
  dev_4_3_coefs[i] = a;
}
