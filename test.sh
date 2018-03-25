#!/bin/bash
make debug

for (( c=1; c<=$2 ; c++ ))
do
    for (( d=0; d<=4; d++ ))
    do
        ./lemipc $1 $d&
        sleep 0.01
    done
done
