const struct {
  unsigned int width;
  unsigned int height;
  unsigned int bytes_per_pixel;
  unsigned char pixel_data[40 * 40 * 2 + 1];
} o = {
  40, 40, 2,
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
  "\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370\037\370"
};
