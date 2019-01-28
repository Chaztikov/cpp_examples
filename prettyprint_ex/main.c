#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "prettyprint.hpp"
using namespace pretty_print;
int main()
{
  std::vector<int>        v;
  std::set<double>        s;
  std::map<size_t, void*> m;
  int                     a[10];

  /* populate containers */

  std::cout << "Vector:  " << v << std::endl
            << "Set:     " << s << std::endl
            << "Map:     " << m << std::endl
            << "C-Array: " << pretty_print::array_wrapper(a) << std::endl;


size_t n = get_number(), m = get_number();
int a[] = {1, 2, 4, 8}; // stack array of static size 4
int * b = new int[n];   // heap array of dynamic size n
int c[m];               // stack array of dynamic size m (VLA)

std::cout << pretty_print::array_wrapper(a)    << std::endl;  // 1
          << pretty_print::array_wrapper(b, n) << std::endl;  // 2
          << pretty_print::array_wrapper(c, m) << std::endl;  // 2
;
return 0;
}



