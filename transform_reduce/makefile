all:
	clang++ -DNDEBUG -O0 -std=gnu++2a -stdlib=libc++ -pedantic -pthread -Wno-all -I/usr/include/leatherman/ -I/usr/include/cppunit/ -I/usr/include/llvm-8/ -I/home/chaztikov/src/libmesh/libmesh-1.3.1/clang-serial/include -I/usr/local/include -I/usr/include/eigen3 -pthread -I/usr/include -lstdc++ -lstdc++fs main.C -o main.o
	1;
	clang++ -O0 -std=gnu++17 -stdlib=libc++ -Wno-all -I${INCLUDE} -pthread -lstdc++ -lstdc++fs main.C -o main.o


