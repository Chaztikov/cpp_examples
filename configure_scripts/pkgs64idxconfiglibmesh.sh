#/bin/bash
#export CC="clang $CPATH -I$PETSC_DIR/ -I$PETSC_DIR/.. -I$PETSC_DIR/../include -I$PETSC_DIR/include"
#export CXX="clang++ $CPATH -I$PETSC_DIR/ -I$PETSC_DIR/.. -I$PETSC_DIR/../include -I$PETSC_DIR/include"

# ../configure PETSC_DIR="$HOME/src/petsc-3.10.4" PESC_ARCH="arch-linux-pkgs-64idx" \
	# --with-dof-id-bytes=8 \
../configure CC=clang CXX=clang++ PETSC_DIR="$HOME/src/petsc-3.10.4" PETSC_ARCH="arch-linux-pkgs-64idx" \
	--with-dof-id-bytes=8 \
	--enable-all=1 \
	--disable-strict-lgpl \
	--disable-warnings \
	--disable-fortran \
	--enable-petsc-required \
	--with-methods="opt" \
	--enable-triangle \
	--enable-tetgen \
	--with-avx512-kernels=1 \
	--with-memalign=64 \
	--with-scalar-type=real \
	--with-debugging=0 \
	#sudo make install
	#&& cp contrib/utils/Make.common .
	#&& make PETSC_DIR=$PETSC_DIR PETSC_ARCH=$PETSC_ARCH -j12 all
