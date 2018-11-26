#create shared lib
gcc -shared bin/shared/add.o bin/shared/answer.o -o bin/shared/libtq84.so
#link dynamically with shared lib
gcc  bin/main.o -Lbin/shared -ltq84 -o bin/use-shared-library
#use sharedlib with LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/bin/shared bin/use-shared-library

