all:
	gcc -c       src/main.c        -o src/main.o
	gcc -c       src/add.c    -o src/add.o
	gcc -c       src/answer.c -o src/answer.o
	gcc -c -fPIC src/add.c    -o src/add.o
	gcc -c -fPIC src/answer.c -o src/answer.o
	gcc -shared src/add.o src/answer.o -o src/libtq84.so
	gcc  src/main.o -L./src -ltq84 -o src/main

clean:
	rm -rf src/*.o  src/*.so src/main