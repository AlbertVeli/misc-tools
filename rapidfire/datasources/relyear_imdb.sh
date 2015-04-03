#!/bin/sh

# Example of getting movie year online from imdb
# (not used)

TITLE="$(perl -MURI::Escape -e 'print uri_escape($ARGV[0]);' "$1")"

URL="http://www.imdb.com/xml/find?xml=1&nr=1&tt=on&q=$TITLE"

curl "$URL" 2>/dev/null -o /tmp/curlout.txt
# Try to get the main title
out=`cat /tmp/curlout.txt | perl -pe "s|.*?$1.*?(\d\d\d\d).*|\1|" | sed '/^[^0-9]/d' | tr -d '\n'`
if test "$out" = ""; then
  # If that fails, try any 4-digit number in the text (might be another film with same name)
  out=`cat /tmp/curlout.txt | perl -pe "s|.*?id=.*?>.*?(\d\d\d\d).*|\1|" | sed '/^[^0-9]/d' | tr -d '\n'`
fi
echo "$out"
