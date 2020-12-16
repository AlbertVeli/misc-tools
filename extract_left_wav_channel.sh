#!/bin/sh

if [ $# != 1 ]; then
	echo "Usage: $0 <stereo_file.wav>"
	echo " Output: left.wav (overwritten if it exists)"
	exit 1
fi

f=$1

rm -f left.wav
ffmpeg -i ${f} -map_channel 0.0.0 left.wav
