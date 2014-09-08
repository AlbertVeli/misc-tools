#!/bin/sh

# Copy all .JPG files in current
# directory to target dir and name
# them img%05d.jpg suitable for conversion
# to movie: ffmpeg -i "img%05d.jpg" [more arguments] out.avi

TARGETDIR=".."

# n = number of first image (in target directory)
n=1

# Loop through all images in current directory
# replace *.JPG below with the names of your images
# sort -n sorts them in numerical order (works
# better for image sequences).
for i in `ls *.JPG | sort -n`; do
  # Copy one image to target dir, with new name
  # that is always consistent, no matter how the
  # source images are numbered.
  cp $i ${TARGETDIR}/`printf "img%05d.jpg" $n`
  # Increase n (sh syntax, a bit weird)
  n=$(($n+1))
done
