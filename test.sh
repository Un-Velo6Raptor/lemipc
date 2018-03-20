make debug
./lemipc $1 2 > a&
./lemipc $1 2 > b&
valgrind ./lemipc $1 1
