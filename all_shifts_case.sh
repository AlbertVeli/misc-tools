#!/bin/bash

# Mixed case variant of all_shifts
# Note, give alphabets as all lowercase
# uppercase duplicates will be generated automatically

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

clearup=`echo $clear | tr '[:lower:]' '[:upper:]'`

clear="${clear}${clearup}"

len=${#ciphr}
for i in `seq 1 $len`; do
  # This substitution syntax needs bash, doesn't work with dash
  rot="${ciphr:$len-$i:$i}${ciphr:0:$len-$i}"
  rotup=`echo $rot | tr '[:lower:]' '[:upper:]'`
  echo "$i: \"${clear}\" --> \"${rot}${rotup}\""
  echo "`substitute $filename \"${clear}\" \"${rot}${rotup}\"`"
done
