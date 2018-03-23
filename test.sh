#!/bin/bash
make debug

for (( c=1; c<=$2 ; c++ ))
do
    ./lemipc $1 2 > a&
    sleep 0.6
done

for (( c=1; c<=$3 ; c++ ))
do
    ./lemipc $1 1 > b&
    sleep 0.6
done

valgrind ./lemipc $1 1
