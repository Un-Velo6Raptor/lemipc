#!/bin/bash
make debug

for (( c=1; c<=$2 ; c++ ))
do
    for (( d=0; d<=3; d++ ))
    do
        ./lemipc $1 $d > a&
        sleep 0.2
    done
done
