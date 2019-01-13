#!/bin/bash
#-stdlib=libc++ -pthread -lgcc -lstd++ -lpetsc
#CXXFLAGS="-g -O0 -Wl -Wno-all -fPIC -fcxx-exceptions -std=gnu++2a"\
#export mcxxflags="-g -O0 -Wl -Wno-all -fPIC -fcxx-exceptions -std=gnu++2a"
#export mlibs="-lstdc++fs"
#export mldflags=$LD_LIBRARY_PATH
#-Wno-all -Qno-unused-arguments -Wno-unused-parameter -Wno-unused
#        CXXFLAGS="-g -O0 -Wl -Wc++17-extensions -Wunused-parameter -Wno-all -fPIC -fcxx-exceptions -std=gnu++2a -stdlib=libc++" \
#CXXFLAGS="-g -O0 -Wno-unused-variable -Wno-unused-parameter -Wno-all -fPIC -fcxx-exceptions -std=gnu++2a -lstdc++fs -lboost_system"

#../configure PETSC_DIR=~/opt/petsc/ PETSC_ARCH=build \
../configure \
	--prefix=$HOME/opt/libmesh/opt/ \
	--enable-all=1 \
	--disable-strict-lgpl \
	--disable-warnings \
	--enable-fortran \
	--enable-petsc \
	--with-methods="opt" \
	--with-mpi=0 \
	--enable-triangle \
	--enable-tetgen \
	--with-shared-libraries=1 \
	--with-avx512-kernels=1 \
	--with-memalign=64 \
	--with-scalar-type=real \
	--with-debugging=1 \
	#&& make -j12 all \
	#&& cp contrib/utils/Make.common .
	#&& make PETSC_DIR=$PETSC_DIR PETSC_ARCH=$PETSC_ARCH -j12 all
