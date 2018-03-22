#!/bin/bash
make debug

for (( c=1; c<=$2 ; c++ ))
do
    ./lemipc $1 1 > a&
done

for (( c=1; c<=$3 ; c++ ))
do
    ./lemipc $1 2 > b&
done

valgrind ./lemipc $1 1
killall lemipc
