#!/usr/bin/env python3

# Crib = known plaintext somewhere in the message
# Key length assumed to be same as crib length
# Infile assumed to be hex encoded. To get hex encoding
# of binary xor ciphertext, run xxd -ps cipher.bin
#
# Plaintext assumed to be printable ascii only, or
# only characters from the string alphabet below.
#
# Numpy is used for faster xor. pip install --user numpy
#
# TODO: add -l <length> argument
#       add different cracking modes. Brute force, dictionary etc.
#       add statistic analysis of decrypted candidates

import sys
import numpy as np

alphabet = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_{}!@-. "\'\n'

# s = %02x encoded hex, out = np array (uint8)
def hex_to_arr(s):
    l = []
    for i in range(0, len(s), 2):
        l.append(int(s[i : i + 2], 16))
    return np.array(l, dtype='B')

# Both ciph and key = array_like numpy objects
def xor(ciph, key):
    return np.bitwise_xor(ciph, key)

def hex_to_str(s):
    ret = ''
    for i in range(0, len(s), 2):
        ret += chr(int(s[i : i + 2], 16))
    return ret

def str_to_hex(s):
    ret = ''
    for c in s:
        ret += '{:02x}'.format(ord(c))
    return ret

def arr_to_hex(a):
    ret = ''
    for i in a:
        ret += chr(i)
    return ret

def str_in_alphabet(s):
    for c in s:
        if not c in alphabet:
            return False
    return True


# --- main

if len(sys.argv) != 3:
    print('Usage:', sys.argv[0], '<crib> <infile>')
    print('')
    print('       crib   = known cleartext string that is in the message')
    print('       infile = hexdump of ciphertext, ie xxd -ps cipher.bin > cipher.hex')
    print('')
    print('       length of the key is assumed to be the same as the crib length (change this later)')
    sys.exit(1)


cribhex = str_to_hex(sys.argv[1])
crib = hex_to_arr(cribhex)
chex = open(sys.argv[2]).read().replace('\n', '')
c = hex_to_arr(chex)
# TODO: give keylen as argument
keylen = len(crib)

keys = []
for i in range(len(c) - keylen):
    cpart = c[i : i + keylen]
    key = xor(cpart, crib)
    keys.append(key)

for k in keys:
    key = []
    for i in range(len(c)):
        key.append(k[i % keylen])
    key = np.array(key, dtype = 'B')
    ma = xor(c, key)
    m = arr_to_hex(ma)
    if m.isprintable() or str_in_alphabet(m):
        print('')
        print(m)
