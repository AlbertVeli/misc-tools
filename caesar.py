#!/usr/bin/env python3
#
# Print all 26 caesar rotations
#
#     caesar.py <filename>
#            or
#     cat ... | caesar.py
#
# ~~=) All Rights Reversed (=~~
##
import string
from sys import argv, stdin

# Use these globals to avoid recreating
# them in every call to init_caesar
clear = string.ascii_lowercase + string.ascii_uppercase
ciph = bytearray(52)

# Return maketrans object for use with str.translate
# (can be adapted for *any* monoalphabetic substitution)
def init_caesar(rot):
    i = 0

    a = ord('a')
    offs = rot - a
    for c in string.ascii_lowercase:
        ciph[i] = (ord(c) + offs) % 26 + a
        i += 1

    a = ord('A')
    offs = rot - a
    for c in string.ascii_uppercase:
        ciph[i] = (ord(c) + offs) % 26 + a
        i += 1

    return str.maketrans(clear, ciph.decode('ascii'))

if len(argv) < 2:
    s = stdin.read()
else:
    with open(argv[1], 'r') as f:
        s = f.read()

# Print all 26 possible rotations
print('0', s)
for i in range(1, 26):
    r = init_caesar(i)
    print(i, s.translate(r))


