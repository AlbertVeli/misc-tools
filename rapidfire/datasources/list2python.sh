#!/bin/sh

# run
# ./list2python.sh > titleyear.py
# to generate python 'title': 'year' dictionary


# aka-titles.list downloaded via http://www.imdb.com/interfaces
if ! test -f 'aka-titles.list'; then
  URL='ftp://ftp.sunet.se/pub/tv+movies/imdb/aka-titles.list.gz'
  curl "$URL" | gunzip | iconv --from-code=ISO-8859-1 --to-code=UTF-8 > aka-titles.list
fi

echo "# -*- coding: utf-8 -*-"
echo ""
echo "titleyear = {"

# Get titles and years into python dictionary format
# using some sedmagheddon. This also tries to fix the
# inconsequent use of "" and '' around title strings.
sed '0,/AKA TITLES LIST/d' aka-titles.list | # Start after this line
grep -v '(aka' aka-titles.list             | # Remove aka (also known as) titles
sed "s/'/\\\'/g"                           | # Replace ' with \'
sed -n "s/\(.*\)[ \t]*(\([0-9][0-9][0-9][0-9]\).\{0,2\}).*/'\1': '\2',/p" | # 'title': 'year',
sed "s/ ': '/': '/" |                        # Remove space before :
sed "s/^'\"/'/" |                            # Remove " at beginning of title
sed "s/\"': '/': '/"                         # Remove " at end of title

echo "}"
