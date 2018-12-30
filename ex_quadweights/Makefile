######################################################################
#
# Template libMesh application Makefile
LIBMESH_DIR := /home/chaztikov/src/libmesh/libmesh-1.3.1/gcc-serial/
# clang-serial-dbg/contrib/bin

# include the library options determined by configure
include $(LIBMESH_DIR)/contrib/utils/Make.common

target     := ./example-$(METHOD)

# ccache mpicxx -DNDEBUG -O0 -felide-constructors -funroll-loops -fstrict-aliasing -Wdisabled-optimization -fopenmp -I/usr/include/eigen3 -I/home/chaztikov/.local/libmesh/linux-all/include  -I/home/chaztikov/.local/petsc//include -I/home/chaztikov/.local/petsc//linux-opt/include -c main.C -o main.x86_64-unknown-linux-gnu.opt.o
# ccache mpicxx -DNDEBUG -O0 -felide-constructors -funroll-loops  -Wdisabled-optimization -I/usr/include/eigen3 -I/home/chaztikov/.local/libmesh/linux-all/include  -I/home/chaztikov/.local/petsc//include -I/home/chaztikov/.local/petsc//linux-opt/include -c main.C -o main.x86_64-unknown-linux-gnu.opt.o###############################################################################
# mpicxx -O2 -felide-constructors -funroll-loops -fstrict-aliasing -Wdisabled-optimization -fopenmp main.x86_64-unknown-linux-gnu.opt.o -o example-opt -Wl,-rpath -Wl,/home/chaztikov/.local/libmesh/linux-all/lib -Wl,-rpath -Wl,/home/chaztikov/.local/petsc/linux-opt/lib /usr/lib/x86_64-linux-gnu/openmpi/lib/openmpi/mca_schizo_ompi.so -Wl,-rpath -Wl,/usr/local/lib -Wl,-rpath -Wl,/usr/lib  -L/home/chaztikov/.local/libmesh/linux-all/lib /home/chaztikov/.local/libmesh/linux-all/lib/libmesh_opt.a -L/home/chaztikov/.local/petsc//linux-opt/lib -L/home/chaztikov/.local/petsc/linux-opt/lib -L/usr/local/lib -L/usr/lib -L/usr/x86_64-linux-gnu/lib /home/chaztikov/.local/libmesh/linux-all/lib/libnetcdf.a /usr/local/lib/libpnetcdf.a /usr/lib/x86_64-linux-gnu/libcurl-gnutls.so /usr/local/lib/libglpk.so -lvtkIOCore-7.1 -lvtkCommonCore-7.1 -lvtkCommonDataModel-7.1 -lvtkFiltersCore-7.1 -lvtkIOXML-7.1 -lvtkImagingCore-7.1 -lvtkIOImage-7.1 -lvtkImagingMath-7.1 -lvtkIOParallelXML-7.1 -lvtkParallelMPI-7.1 -lvtkParallelCore-7.1 -lz -lpetsc -lsuperlu_dist -lHYPRE -llapack -lblas /home/chaztikov/.local/petsc/linux-opt/lib/libhdf5hl_fortran.a /home/chaztikov/.local/petsc/linux-opt/lib/libhdf5_fortran.a /home/chaztikov/.local/petsc/linux-opt/lib/libhdf5_hl.a /home/chaztikov/.local/petsc/linux-opt/lib/libhdf5.a -lmpi_usempif08 -lmpi_usempi_ignore_tkr -lmpi_mpifh -lmpi -lgfortran -lm -lgcc_s -lquadmath -lpthread -lstdc++ -ldl -L/usr/lib/x86_64-linux-gnu/openmpi/lib -L/usr/lib/gcc/x86_64-linux-gnu/7 -L/usr/lib/x86_64-linux-gnu -L/lib/x86_64-linux-gnu -pthread -fopenmp
# File management.  This is where the source, header, and object files are
# defined

#
# source files
srcfiles 	:= $(wildcard *.C)

#
# object files
objects		:= $(patsubst %.C, %.$(obj-suffix), $(srcfiles))
###############################################################################



.PHONY: dust clean distclean

###############################################################################
# Target:
#

all:: $(notdir $(target))

# Production rules:  how to make the target - depends on library configuration
$(notdir $(target)): $(objects)
	@echo "Linking "$@"..."
	@$(libmesh_LIBTOOL) --tag=CXX $(LIBTOOLFLAGS) --mode=link \
	  $(libmesh_CXX) $(libmesh_CXXFLAGS) $(objects) -o $@ $(libmesh_LIBS) $(libmesh_LDFLAGS) $(EXTERNAL_FLAGS)


# Useful rules.
dust:
	@echo "Deleting old output and runtime files"
	@rm -f out*.m job_output.txt output.txt* *.gmv.* *.plt.* out*.xdr* out*.xda* PI* complete

clean: dust
	@rm -f $(objects) *.$(obj-suffix) *.lo

clobber: clean 
	@rm -f $(target)

distclean: clean
	@rm -rf *.o .libs

echo:
	@echo srcfiles = $(srcfiles)
	@echo objects = $(objects)
	@echo target = $(target)
	@echo $(libmesh_LIBTOOL)

run: complete

complete: $(wildcard *.in)
#	@$(MAKE) dust
	@$(MAKE) -C $(dir $(target)) $(notdir $(target))
	@echo "***************************************************************"
	@echo "* Running App " $(notdir $(target))
	@echo "***************************************************************"
	@echo " "
	${LIBMESH_RUN} $(target) -Wno-unused-variable ${LIBMESH_OPTIONS} 2>&1 | tee output.txt
	@bzip2 -f output.txt
	@echo " "
	@echo "***************************************************************"
	@echo "* Done Running App " $(notdir $(target))
	@echo "***************************************************************"

###############################################################################
