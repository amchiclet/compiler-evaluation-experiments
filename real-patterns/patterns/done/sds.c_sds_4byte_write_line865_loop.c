declare write_samples[];
declare ucptr[];
declare sample;

for [(k, +=4)] {
  sample = write_samples[k / 4];
  sample = sample + 0x80000000;
  ucptr[k] = sample >> 25 & 0x7F;
  ucptr[k + 1] = sample >> 18 & 0x7F;
  ucptr[k + 2] = sample >> 11 & 0x7F;
  ucptr[k + 3] = sample >> 4 & 0x7F;
}
