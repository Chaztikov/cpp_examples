all:
	clang++ -DNDEBUG -O0 -std=gnu++2a -pedantic -pthread -Wno-all -I/usr/include/cppunit/ -I/usr/include/llvm-7/ -I/usr/include/eigen3 -pthread -I/usr/include -c main.C -o main.o
	clang++ -O0 -std=gnu++2a -pedantic -pthread -Wno-all -I/usr/include/llvm-7/ main.o -o example-opt -Wl,-rpath /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so -ldl /usr/local/lib/libglpk.so -lm -lz -lrt -fopenmp -pthread