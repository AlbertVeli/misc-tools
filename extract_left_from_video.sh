#!/bin/sh

# Extract left audio channel from video with
# stereo sound.

if [ $# != 1 ]; then
	echo "Usage: $0 <video.mov>"
	echo " Output: left.wav (overwritten if it exists)"
	exit 1
fi

STEREO=$(mktemp -u).wav || exit 1
ffmpeg -i $1 ${STEREO} || exit 1

rm -f left.wav
ffmpeg -i ${STEREO} -map_channel 0.0.0 left.wav || exit 1
rm -f ${STEREO}

echo "left.wav successfully created"
