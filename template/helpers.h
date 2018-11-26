#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cmath>
#include <ctime>
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
#include <cassert>

#include <memory>
#include <utility>
#include <array>
#include <valarray>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

std::valarray<float> linspace(float start, float stop, const unsigned int size)
{
    std::valarray<float> v(size);
    for(int i=0; i<size; i++) v[i] = start + i * (stop-start)/size;
    return v;
}

std::valarray<float> arange(float start, float step, float stop)
{
    int size = (stop - start) / step;
    std::valarray<float> v(size);
    for(int i=0; i<size; i++) v[i] = start + step * i;
    return v;
}

std::string psstm(std::string command)
{//return system call output as std::string
    std::string s;
    char tmp[1000];
    FILE* f = popen(command.c_str(), "r");
    while(fgets(tmp, sizeof(tmp), f)) s += tmp;
    pclose(f);
    return s;
}

std::string plot(const std::valarray<float>& x, const std::valarray<float>& y)
{
    int sz = x.size();
    assert(sz == y.size());
    int bytes = sz * sizeof(float) * 2;
    const char* name = "plot1";
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, bytes);
    float* ptr = (float*)mmap(0, bytes, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    for(int i=0; i<sz; i++) {
        *ptr++ = x[i];
        *ptr++ = y[i];
    }

    std::string command = "python plot.py ";
    std::string s = psstm(command + std::to_string(sz));
    shm_unlink(name);
    return s;
}

// Linear interpolation following MATLAB linspace
std::vector<float> LinearSpacedArray(float a, float b, std::size_t N)
{
    float h = (b - a) / static_cast<float>(N-1);
    std::vector<float> xs(N);
    std::vector<float>::iterator x;
    float val;
    for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h) {
        *x = val;
    }
    return xs;
}