all:
	c++ -std=c++17 -stdlib=libc++ -I${INCLUDE} -L/usr/lib/x86_64-linux-gnu -lc++fs -lgsl -lgslcblas -lm main.c -c
	c++ -L/usr/lib/x86_64-linux-gnu -lgsl -lgslcblas -lm main.o -o main


