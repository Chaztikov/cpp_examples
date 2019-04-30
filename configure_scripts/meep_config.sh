This script successfully builds meep on a clean CentOS 6 install.
Though I probably makes sense to break it up...
Building swig and Guile may not be necessary, though I remember having problems with the ones that came with CentOS 6

I build OpenMPI, HDF5 and Python3 because the versions that come with CentOS 6 are hopelessly out of date.

#!/bin/bash

set -e

RPATH_FLAGS="-Wl,-rpath,/usr/local/lib:/usr/local/lib/openmpi"
MY_LDFLAGS="-L/usr/local/lib -L/usr/local/lib/openmpi ${RPATH_FLAGS}"
MY_CPPFLAGS="-I/usr/local/include -I/usr/local/include/openmpi"

#
# yum installs
#
sudo yum -y --enablerepo=extras install epel-release
sudo yum -y install bison byacc cscope ctags cvs diffstat doxygen flex gcc gcc-c++ gcc-gfortran gettext git indent intltool libtool patch patchutils rcs redhat-rpm-config rpm-build subversion systemtap wget
sudo yum -y install openblas-devel fftw3-devel libpng-devel gsl-devel gmp-devel pcre-devel libtool-ltdl-devel libunistring-devel libffi-devel gc-devel zlib-devel openssl-devel sqlite-devel bzip2-devel

#
# time to build
#
sudo rm -rf ~/install
mkdir -p ~/install


cd ~/install
wget https://github.com/swig/swig/archive/rel-3.0.12.tar.gz
tar xvf rel-3.0.12.tar.gz
cd swig-rel-3.0.12
./autogen.sh
./configure
make -j
sudo make -j install


cd ~/install
wget https://ftp.gnu.org/gnu/guile/guile-2.0.11.tar.gz
tar xvf guile-2.0.11.tar.gz
cd guile-2.0.11
./configure
make -j
sudo make -j install


cd ~/install
wget https://www.python.org/ftp/python/3.6.5/Python-3.6.5.tgz
tar xvf Python-3.6.5.tgz
cd Python-3.6.5
./configure --enable-optimizations
make -j
sudo make -j install


cd ~/install
wget https://download.open-mpi.org/release/open-mpi/v2.1/openmpi-2.1.1.tar.gz
tar xvf openmpi-2.1.1.tar.gz
cd openmpi-2.1.1/
./configure
make -j all
sudo make -j install


cd ~/install
git clone https://bitbucket.hdfgroup.org/scm/hdffv/hdf5.git
cd hdf5/
git checkout tags/hdf5-1_10_2
./configure --enable-parallel --enable-shared --prefix=/usr/local CC=/usr/local/bin/mpicc CXX=/usr/local/bin/mpic++
make -j
sudo make -j install


cd ~/install
git clone https://github.com/stevengj/harminv.git
cd harminv/
sh autogen.sh --enable-shared
make -j
sudo make -j install


cd ~/install
git clone https://github.com/stevengj/libctl.git
cd libctl/
sh autogen.sh  --enable-shared
make -j
sudo make -j install


cd ~/install
git clone https://github.com/stevengj/h5utils.git
cd h5utils/
sh autogen.sh CC=/usr/local/bin/mpicc LDFLAGS="${MY_LDFLAGS}" CPPFLAGS="${MY_CPPFLAGS}"
make -j
sudo make -j install

cd ~/install
git clone https://github.com/stevengj/mpb.git
cd mpb/
sh autogen.sh --enable-shared CC=/usr/local/bin/mpicc LDFLAGS="${MY_LDFLAGS}" CPPFLAGS="${MY_CPPFLAGS}" --with-hermitian-eps
make -j
sudo make -j install


cd ~/install
wget https://bitbucket.org/mpi4py/mpi4py/downloads/mpi4py-3.0.0.tar.gz
tar xvf mpi4py-3.0.0.tar.gz
cd mpi4py-3.0.0/
python3 setup.py build
sudo /usr/local/bin/python3 setup.py install


cd ~/install
wget https://github.com/h5py/h5py/archive/2.8.0.tar.gz
tar xvf 2.8.0.tar.gz
cd h5py-2.8.0/
python3 setup.py configure --mpi
python3 setup.py build
sudo /usr/local/bin/python3 setup.py install


cd ~/install
git clone https://github.com/stevengj/meep.git
cd meep/
sh autogen.sh --enable-shared --with-mpi PYTHON=python3 MPICC=/usr/local/bin/mpicc MPICXX=/usr/local/bin/mpic++ LDFLAGS="${MY_LDFLAGS}" CPPFLAGS="${MY_CPPFLAGS}"
#sh autogen.sh --enable-shared --with-mpi PYTHON=python3 CC=/usr/local/bin/mpicc CXX=/usr/local/bin/mpic++ LDFLAGS="${MY_LDFLAGS}" CPPFLAGS="${MY_CPPFLAGS}"
make -j
#sed -i 's/CC="mpic++"/CC="\/usr\/local\/bin\/mpic++"/g' libtool
sudo make install
