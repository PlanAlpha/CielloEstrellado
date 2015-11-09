#!/bin/sh

RATE=0.7
MAX=$1
MIN=$2
a=`echo "$1 - $2" | bc`
b=`echo "$a * $RATE" | bc`
c=`echo "$b + $MIN" | bc`

echo $c

unset MAX
unset MIN
unset RATE
