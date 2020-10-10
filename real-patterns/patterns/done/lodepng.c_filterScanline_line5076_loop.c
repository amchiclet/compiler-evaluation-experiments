declare out[];
declare scanline[];
declare prevline[];

for [(i, >=bytewidth)] {
  out[i] = scanline[i] - (scanline[i - bytewidth] + prevline[i]) / 2;
}
