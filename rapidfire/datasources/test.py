#!/usr/bin/env python

# Test if the generated titleyear.py file works

import sys
sys.path.append('.')

from titleyear  import titleyear

# Give title on cmdline
title = ' '.join(sys.argv[1:])

# Print out year of title
if title in titleyear:
  print titleyear[title]
else:
  print '"' + title + '"' + " not found"
