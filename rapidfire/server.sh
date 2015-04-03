#!/bin/sh

round ()
{
    echo ""
    echo "################################"
    echo "#######     ROUND $1        #####"
    echo "################################"
    echo ""
    echo ""
    echo ""
}

echo "################################"
echo "################################"
echo "#######                    #####"
echo "#######     RAPIDFIRE      #####"
echo "#######                    #####"
echo "################################"
echo "################################"
echo ""
echo ""
echo "Welcome to RAPIDFIRE. Give answers and get the flag."


round 1
echo "What is the sum of first 3967746430 natural odd numbers"
read p
if test "$p" != "15743011732777744900"; then
    echo "Wrong answer"
    exit 1
fi
echo "Good job"

round 2
echo "What is the md5 hash of 2589813708"
read p
if test "$p" != "3e0f6256f5145a094da34c3f6c8e5c46"; then
    echo "Wrong answer"
    exit 1
fi
echo "Smartass!"

round 3
echo "So tell me the sum of first 1234 natural odd numbers"
read p
if test "$p" != "1522756"; then
    echo "Wrong answer"
    exit 1
fi
echo "Well done!"

round 4
echo "So tell me the sum of first 5 natural numbers"
read p
if test "$p" != "15"; then
    echo "Wrong answer"
    exit 1
fi
echo "Nailed it"

round 5
echo "Next up, what's the 297850th digit in pi"
read p
if test "$p" != "9"; then
    echo "Wrong answer"
    exit 1
fi
echo "Rocker!"

round 6
echo "What is the country of Porto Novo"
read p
if test "$p" != "Benin"; then
    echo "Wrong answer"
    exit 1
fi
echo "Who are you?"

round 7
echo "Show me the value of 7160269243 in binary"
read p
if test "$p" != "110101010110010010000100110111011"; then
    echo "Wrong answer"
    exit 1
fi
echo "STFU!"

round 8
echo "Show me the 194th fibonacci number"
read p
if test "$p" != "15635695580168194910579363790217849593217"; then
    echo "Wrong answer"
    exit 1
fi
echo "You rock!"

round 9
echo "Give me the 511286th prime number"
read p
if test "$p" != "7548007"; then
    echo "Wrong answer"
    exit 1
fi
echo "Are you for real?"

round 10
echo "Show me the 2 digit code of Timor-Leste"
read p
if test "$p" != "TL"; then
    echo "Wrong answer"
    exit 1
fi
echo "Wanna play more?"

round 11
echo "Give me the release year of About Time"
read p
if test "$p" != "2013"; then
    echo "Wrong answer"
    exit 1
fi
echo "Good work!"

round 12
echo "Do you know what's the country of N'Djamena"
read p
if test "$p" != "Chad"; then
    echo "Wrong answer"
    exit 1
fi
echo "STFU!"

round 13
echo "Next up, what's the release year of Constantine"
read p
if test "$p" != "2005"; then
    echo "Wrong answer"
    exit 1
fi
echo "Rocker!"

round 14
echo "What is the country of Bandar Seri Begawan"
read p
if test "$p" != "Brunei"; then
    echo "Wrong answer"
    exit 1
fi
echo "Nailed it"

round 15
echo "What is the 2 digit code of Saint Kitts and Nevis"
read p
if test "$p" != "KN"; then
    echo "Wrong answer"
    exit 1
fi
echo "Don't mess with me!"

round 16
echo "Show me the 0th fibonacci number"
read p
if test "$p" != "0"; then
    echo "Wrong answer"
    exit 1
fi
echo "You rock!"

round 17
echo "Do you know what's the release year of Spider-Man: The Dragon's Challenge"
read p
if test "$p" != "1979"; then
    echo "Wrong answer"
    exit 1
fi
echo "STFU!"

round 18
echo "Do you know what's the release year of Chi trova un amico trova un tesoro"
read p
if test "$p" != "1981"; then
    echo "Wrong answer"
    exit 1
fi
echo "Nailed it"

round 19
echo 'What is the release year of Moulin Rouge!'
read p
if test "$p" != "2001"; then
    echo "Wrong answer"
    exit 1
fi
echo "Nailed it"

round 20
echo "What is the 2 digit code of Cocos (Keeling) Islands"
read p
if test "$p" != "CC"; then
    echo "Wrong answer"
    exit 1
fi
echo "Who are you?"

echo ""
echo "flag: **flag**"

exit 0
