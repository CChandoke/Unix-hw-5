# build dealer
g++ -std=c++11 -o dealer dealer.cpp -I$HOME/local/gsl-2.5/include/

# build hand
gcc -o hand hand.c -lgslcblas -lgsl -L$HOME/local/gsl-2.5/lib/ -I$HOME/local/gsl-2.5/include/ -Wl,-rpath=$HOME/local/gsl-2.5/lib/


