#!/bin/sh

# Example of getting release year from omdb
# (not used)

TITLE="$(perl -MURI::Escape -e 'print uri_escape($ARGV[0]);' "$1")"

URL="http://www.omdbapi.com/?t=$TITLE"

#echo "URL = $URL"
curl "$URL" 2>/dev/null | sed 's/.*"Year":"\([0-9]*\)".*/\1/'
