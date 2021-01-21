#!/bin/bash

# Compile the converter.
gcc png_pal_rgb_2_header.c -lpng -o png2h

# Split the atlases into images.
# Exclude the background chunk to limit the palette to the minumum size.
convert kenney_16x16_tiles.png -crop 16x16 -background red -define png:exclude-chunk=bKGD tile_%03d.png
convert kenney_256x32_backgrounds.png -crop 256x32 -background red -define png:exclude-chunk=bKGD bg_%03d.png

# Generate the headers.
/bin/ls tile_* | while read f; do ./png2h $f; done | sed 's/\.png//g' > tiles.h
/bin/ls bg_00* | while read f; do ./png2h $f; done | sed 's/\.png//g' > backgrounds.h

printf "\nstatic const uint16_t* tile_pals[] = {\n" >> tiles.h
cat tiles.h | grep -o tile_[0-9][0-9][0-9]_pal | sed "s/pal/pal,/g" >> tiles.h

printf "};\n\nstatic const uint8_t* tile_datas[] = {\n" >> tiles.h
cat tiles.h | grep -o tile_[0-9][0-9][0-9]_data | sed "s/data/data,/g" >> tiles.h

cat tiles.h | grep PaletteSize  > palsizes.h

cat tiles.h | grep -v PaletteSize > ../assets.h
printf "};\n\nstatic const PaletteSize palSizes[] = {\n" >> ../assets.h
cat palsizes.h >> ../assets.h
printf "\n};" >> ../assets.h

cat backgrounds.h | grep -v PaletteSize >> ../assets.h

rm -fr tile_*.png bg_*.png png2h tiles.h backgrounds.h palsizes.h
