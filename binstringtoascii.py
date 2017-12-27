#!/usr/bin/env python3

# ~~=) All Rights Reversed (=~~

import sys

# Get input from stdin or argv[1]
if len(sys.argv) == 1:
	f = sys.stdin
else:
	f = open(sys.argv[1])

# Read the whole file into binstr
binstr = f.read()
# Done with f, close it
f.close()
# Add 0b at beginning and remove all whitespace
binstr = '0b' + binstr.replace(' ', '').replace('\t', '').replace('\n', '')
# Convert to ascii
n = int(binstr, 2)
s = n.to_bytes((n.bit_length() + 7) // 8, 'big').decode()
print(s)
