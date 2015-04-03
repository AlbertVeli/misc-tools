#!/usr/bin/env python
#
# -*- coding: utf-8 -*-
#
# Originally written by Albert Veli
# during the BackdoorCTF15 competition
# on April 2 2015 to solve the rapid
# fire challenge.
#
# https://backdoor.sdslabs.co/
#
# Since then I moved some datasources
# into the datasources subdirectory to
# make this script more easy to read.
#
# The script could easily be modified to
# communicate with different types of services.
#
# Pungenday, the 20th day of Discord in the YOLD 3181
#
# ~~=) All Rights Reversed (=~~

import sys
import md5
import pexpect

# Import get_title_year, getccode and getcountry
# routines from the datasources dir
sys.path.append('datasources')
from gettitleyear  import get_title_year
from ccodes import getccode
from cities import getcountry

# Set to False to remove debug output
debug = True
def dbg(s):
    if (debug):
        print "DBG: " + s

# The functions below each solve one kind of problem
def getmd5(s):
    m = md5.new()
    m.update(s)
    return m.hexdigest()

def getodd(s):
    n = int(s)
    return str(n * n)

def getnat(s):
    n = int(s)
    return str(n * (n + 1) / 2)

def getpi(s):
    n = int(s)
    if (n > 1000000):
        print "Error: only got 1 million decimals, returning 1"
        return '1'
    fo = open("datasources/piM.txt", "r")
    fo.seek(n)
    ans = fo.read(1)
    fo.close()
    return ans

def getprime(s):
    n = int(s)
    if (n > 1000000):
        print "Error: only got 1 million primes, return 1"
        return '1'
    fo = open("datasources/primesM.txt", "r")
    #for x in xrange(n - 1):
    for x in xrange(n - 0):
        fo.readline()
    ans = fo.readline().rstrip()
    fo.close()
    return ans

# Call external libgmp program fib, from:
# https://github.com/AlbertVeli/misc-tools
def fib(n):
    cmd = 'fib ' + str(n)
    child = pexpect.spawn(cmd)
    child.expect(['\n', pexpect.EOF, pexpect.TIMEOUT])
    ans = child.before.rstrip()
    child.close()
    return long(ans)

def getfib(s):
    n = long(s)
    return str(fib(n))

def getfibsum(s):
    n = long(s)
    return str(fib(n + 2) - 1)

def getbin(s):
    n = int(s)
    return bin(n)[2:]

def get_title_year_imdb(n):
    cmd = 'datasources/relyear_imdb.sh ' + str(n)
    child = pexpect.spawn(cmd)
    child.expect(['\n', pexpect.EOF, pexpect.TIMEOUT])
    ans = child.before.rstrip()
    child.close()
    return ans

def get_title_year_omdb(n):
    cmd = 'datasources/relyear_omdb.sh ' + str(n)
    child = pexpect.spawn(cmd)
    child.expect(['\n', pexpect.EOF, pexpect.TIMEOUT])
    ans = child.before.rstrip()
    child.close()
    return ans


# Main program

#server = server = pexpect.spawn('cat pipa')
#server = pexpect.spawn('nc 128.199.107.60 8008')
server = pexpect.spawn('nc localhost 6666')

# Log pexpect interation to this file
fout = file('expectlog.txt','w')
server.logfile = fout

while (True):

    # Each question begins with one of
    # the 5 phrases below. Filter them out
    # from the rest of the text with expect
    index = server.expect (['what\'s the ',
                            'What is the ',
                            'So tell me the ',
                            'Give me the ',
                            'Show me the ',
                            pexpect.EOF, pexpect.TIMEOUT])

    # server.before contains skipped since last
    # call to expect up until the current match
    print server.before

    # index is the number of pattern that matched
    if (index > 4):
        print "Done"
        print server.before
        exit(0)

    # After the opening phrase comes a question
    # Some examples of how they could look:
    #
    # What is the md5 hash of 2589813708
    # What is the sum of first 3967746430 natural odd numbers
    # Do you know what's the sum of first 1649568010 natural numbers
    # So tell me the 399670th digit in pi
    # Next up, what's the 930542nd prime number
    # So tell me the sum of first 205 fibonacci numbers
    # Do you know what's the country of Managua
    # Give me the value of 937900817 in binary
    # What is the 2 digit code of Saint Kitts and Nevis
    # Next up, what's the release year of Constantine
    #
    # The regular expressions below try to catch all these.
    # Text between ( and ) in the regular expression
    # can be retrieved afterwards with match.group(1)
    # (\d+)[tsrn][htd] for instance means catch one or
    # more digits followed by any combination of t, s, r, or n
    # and h, t or d. This matches strings like 23rd, 132nd, 5th
    # and 51st putting the number string in match.group(1)

    index = server.expect (['md5 hash of (\d+)',
                            'sum of first (\d+) natural odd numbers',
                            'sum of first (\d+) natural numbers',
                            '(\d+)[tsrn][htd] digit in pi',
                            '(\d+)[tsrn][htd] prime number',
                            'sum of first (\d+) fibonacci numbers',
                            'country of ([.\'a-zA-Z ]+)',
                            'value of (\d+) in binary',
                            '(\d+)[tsrn][htd] fibonacci number',
                            '2 digit code of ([.,a-zA-Z -]+)',
                            'release year of ([.\'0-9a-zA-Z&:! -]+)',
                            pexpect.EOF, pexpect.TIMEOUT])

    # If index > 10 then we either got EOF or a TIMEOUT
    if (index > 10):
        print "Done, server.before: "
        print server.before
        server.close()
        fout.close()
        exit(0)

    # Get the important part of the question into the string num
    num = server.match.group(1).rstrip()

    try:

        # index is the type of question
        if (index == 0):
            ans = getmd5(num)
            dbg("md5 of " + num + " = " + ans)
        elif (index == 1):
            ans = getodd(num)
            dbg("sum of first " + num + " odd numbers = " + ans)
        elif (index == 2):
            ans = getnat(num)
            dbg("sum of first " + num + " natural numbers = " + ans)
        elif (index == 3):
            ans = getpi(num)
            dbg("pi digit #" + num + " = " + ans)
        elif (index == 4):
            ans = getprime(num)
            dbg("prime #" + num + " = " + ans)
        elif (index == 5):
            ans = getfibsum(num)
            dbg("fibsum(" + num + ") = " + ans)
        elif (index == 6):
            ans = getcountry(num)
            dbg("country of " + num + " = " + ans)
        elif (index == 7):
            ans = getbin(num)
            dbg("bin of " + num + " = " + ans)
        elif (index == 8):
            ans = getfib(num)
            dbg("fib(" + num + ") = " + ans)
        elif (index == 9):
            ans = getccode(num)
            dbg("2 digit code of " + num + " = " + ans)
        elif (index == 10):
            ans = get_title_year(num)
            #ans = get_title_year_imdb(num)
            #ans = get_title_year_omdb(num)

            dbg("release year of " + num + " = " + ans)

    # This catches if user presses Ctrl-C
    except KeyboardInterrupt:
        print "Keyboard interrupt at: "
        print server.before
        print "index = " + str(index)
        server.close()
        fout.close()
        exit(0)

    # Remove possible whitespace and newlines from ans
    ans = ans.rstrip()

    # And send the answer
    server.sendline(ans)

# Close the logfile
fout.close()
