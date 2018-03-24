#!/bin/bash
make debug

for (( c=1; c<=$2 ; c++ ))
do
    ./lemipc $1 2 > a&
    sleep 0.2

    if [ $c -lt $2 ]
    then
        ./lemipc $1 1 > b&
        sleep 0.2
    fi

done

valgrind ./lemipc $1 1
