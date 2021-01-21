#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PNG_DEBUG 3
#include <png.h>

void abort_(const char* s, ...) {
  va_list args;
  va_start(args, s);
  vfprintf(stderr, s, args);
  fprintf(stderr, "\n");
  va_end(args);
  abort();
}

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep* row_pointers;

void read_png_file(char* file_name) {
  char header[8];  // 8 is the maximum size that can be checked

  /* open file and test for it being a png */
  FILE* fp = fopen(file_name, "rb");
  if (!fp)
    abort_("[read_png_file] File %s could not be opened for reading", file_name);
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8))
    abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);

  /* initialize stuff */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    abort_("[read_png_file] png_create_read_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    abort_("[read_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
    abort_("[read_png_file] Error during init_io");

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  if (color_type == PNG_COLOR_TYPE_PALETTE) {
    png_colorp palette;
    int num_palette;
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    printf("\nstatic const uint16_t __restrict__ %s_pal[%d] = { ", file_name, num_palette);
    for (int i = 0; i < num_palette; i++) {
      // fedcba9876543210
      //        rrrrrrrr
      // rrrrr000
      //        gggggggg
      //     gggggg00
      //        bbbbbbbb
      //           bbbbb
      unsigned int rgb565 = 0x0000;
      rgb565 |= ((unsigned int)(palette[i].red & 0b11111000)) << 8;
      rgb565 |= ((unsigned int)(palette[i].green & 0b11111100)) << 3;
      rgb565 |= ((unsigned int)(palette[i].blue & 0b11111000)) >> 3;
      printf("0x%04X, ", rgb565);
    }
    printf("};\n");

    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
      abort_("[read_png_file] Error during read_image");

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (y = 0; y < height; y++)
      row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));

    png_read_image(png_ptr, row_pointers);

    fclose(fp);

    // bits per pixel:       0  1  2  3  4  5  6  7  8
    unsigned char mult[9] = {0, 8, 4, 0, 2, 0, 0, 0, 1};
    unsigned char size[9] = {0, 2, 4, 8, 16, 32, 64, 128, 0};

    printf("\nstatic const uint8_t __restrict__ %s_data[] = { %d, %d, \n", file_name, width,
           height);
    for (y = 0; y < height; y++) {
      png_byte* row = row_pointers[y];
      for (x = 0; x < width / mult[bit_depth]; x++) {
        printf("0x%02x, ", row[x]);
      }
      printf("\n");
    }
    printf("};\n");

    printf("PaletteSize::PAL%d,\n", size[bit_depth]);
  }
}

int main(int argc, char** argv) {
  if (argc != 2)
    abort_("Usage: program_name <file_in>>");

  read_png_file(argv[1]);

  return 0;
}
