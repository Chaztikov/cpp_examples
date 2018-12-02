
#include "boost/multi_array.hpp"
#include <cassert>

/*
range
*/
  // [base,stride,bound)
  // [0,2,4) 

  typedef boost::multi_array_types::index_range range;
  range a_range;
  a_range = range(0,4,2);
  a_range = range().start(0).finish(4).stride(2);
  a_range = range().start(0).stride(2).finish(4);
  a_range = 0 <= range().stride(2) < 4;
  a_range = 0 <= range().stride(2) <= 3;



int 
main () {
  // Create a 3D array that is 3 x 4 x 2
  typedef boost::multi_array<double, 3> array_type;
  typedef array_type::index index;
  array_type A(boost::extents[3][4][2]);

  // Assign values to the elements
  int values = 0;
  for(index i = 0; i != 3; ++i) 
    for(index j = 0; j != 4; ++j)
      for(index k = 0; k != 2; ++k)
        A[i][j][k] = values++;

  // Verify values
  int verify = 0;
  for(index i = 0; i != 3; ++i) 
    for(index j = 0; j != 4; ++j)
      for(index k = 0; k != 2; ++k)
        assert(A[i][j][k] == verify++);

  return 0;
}

