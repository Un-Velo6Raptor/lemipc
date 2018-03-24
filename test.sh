#!/bin/bash
make debug

for (( c=1; c<=$2 ; c++ ))
do
    for (( d=0; d<62; d++ ))
    do
        ./lemipc $1 $d > a&
        sleep 0.1
    done
done