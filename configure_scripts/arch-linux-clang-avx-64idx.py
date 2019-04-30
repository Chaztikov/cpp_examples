#!/usr/bin/env python

configure_options = [
  #'--download-mpich',
  '--with-clean=1',
  '--with-mpi=0',
  '--with-64-bit-indices=1',
  '--with-cc=clang',
  '--with-cxx=clang++',
  '--with-fc=0',
  'CFLAGS=-mavx',
  '--with-cxx-dialect=C++11',
  '--with-zlib=1',
  ]

if __name__ == '__main__':
  import sys,os
  sys.path.insert(0,os.path.abspath('config'))
  import configure
  configure.petsc_configure(configure_options)

