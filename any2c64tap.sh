#!/bin/sh

# wav2tap is very picky about the wav format.
# Default ffmpeg output doesn't work.
# Use sox to create compatible wav file.
# Probably possible with some ffmpeg parameters too.

if test "$1" == ""; then
	echo "Usage: $0 <c64tapeaudio.wav> [outfile.tap]"
	exit 1
fi

input=$1

if test "$2" != ""; then
	outfile="$2"
else
	outfile='out.tap'
fi


# Put path to wav2tap binary here
# (from https://github.com/lunderhage/c64tapedecode)
wav2tap='/usr/local/bin/wav2tap'

# Use hard to predict tempfile names
rawtmp=$(mktemp /tmp/outXXXXX).raw
wavtmp=$(mktemp /tmp/outXXXXX).wav

cleanup()
{
	rm -f $rawtmp $wavtmp
}

fail()
{
	echo "Error: $1"
	cleanup
	exit 1
}

# Make sure tmpfiles doesn't exist
cleanup

ffmpeg -i $input -ac 1 -f s16le -c:a pcm_s16le $rawtmp || fail 'ffmpeg failed'
sox -r 48k -e signed -b 16 $rawtmp $wavtmp || fail 'sox failed'
wav2tap $wavtmp > $outfile || fail 'wav2tap failed'

echo "$outfile successfully created"
cleanup
