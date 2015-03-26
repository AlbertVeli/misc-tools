#!/bin/bash

filename=$1
clear=$2
ciphr=$3

if test "$ciphr" = ""; then
  echo "Usage: $0 <filename> <clear alphabet> <cipher alphabet>"
  echo "EXAMPLES"
  echo
  echo "Caesar with all possible shifts:"
  echo
  echo "  $0 1.txt \"abcdefghijklmnopqrstuvwxyz\" \"abcdefghijklmnopqrstuvwxyz\""
  echo
  echo "Reverse alphabet with all possible shifts:"
  echo
  echo "  $0 1.txt \"abcdefghijklmnopqrstuvwxyz\" \"zyxwvutsrqponmlkjihgfedcba\""
  echo
fi

len=${#ciphr}
for i in `seq 1 $len`; do
  # This substitution syntax needs bash, doesn't work with dash
  echo "\"$clear\" \"${ciphr:$len-$i:$i}${ciphr:0:$len-$i}\""
  echo "`substitute $filename \"$clear\" \"${ciphr:$len-$i:$i}${ciphr:0:$len-$i}\"`"
done
