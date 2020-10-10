declare diff;
declare dest[];
declare last_val;
declare src[];

for [k] {
  diff = ((src[k] >> 16) - last_val);
  dest[k] = diff;
  last_val =(src[k] >> 16);
}
