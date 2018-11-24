// #include "./param_pack_ex_structs.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <math.h>
#include <stdint.h>
#include <sys/time.h>
#include <typeinfo>
#include <utility>
#include <any>
#include <vector>
#include <climits>
#include <cstdint>
#include <type_traits>
#include <utility>

#include <vector>
#include <numeric>
#include <string>
#include <functional>

template <typename... Args>
void FoldWrite(
    std::ofstream &outfile,
    Args &&... args)
{
    (outfile << ... << std::forward<Args>(args)) << "\n";
}

int main()
{
	double L1error =1., L2error=2.;
	std::string savename("test_error");
	std::ofstream outfile;
	outfile.open(savename, std::ios_base::app);
	FoldWrite(outfile, L1error, L2error);
	
}