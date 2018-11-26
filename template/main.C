#include "./helpers.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include "math.h"

std::valarray<float> f(std::valarray<float> x);
std::valarray<float> f(std::valarray<float> x)
{
  return sin(x) + sin(3.0f * x) / 3.0f + sin(5.0f * x) ;
}

float kernel_CubicConvolution(float x, const float &a);
std::valarray<float> kernel_CubicConvolution(std::valarray<float> xx, const float &a = -0.5)
{
  std::valarray<float> vals(xx.size(),0.);
    // float a = -0.5;
  // std::valarray xx = std::abs(x);
for(int i=0; i<xx.size(); i++) {
    float x = xx[i];
    float val = vals[i];
    if (std::abs(x) <= 0.5)
        val += 1 - 4 * (3. + a) * std::pow(abs(x), 2) + 8 * (2. + a) * std::pow(abs(x), 3);
    else if (std::abs(x) <= 1.)
        val += 4 * a * std::pow((-1 + abs(x)), 2) * (-1 + 2 * abs(x));
    else
        0;
  }
    return vals;
}

float kernel_linear(float x, const float &a);
std::valarray<float> kernel_linear(const std::valarray<float> & xx, const float &a = -0.5)
{
  std::valarray<float> vals(xx.size(),0.);
    // float a = -0.5;
  // std::valarray xx = std::abs(x);
for(int i=0; i<xx.size(); i++) {
    vals[i] = - std::abs(xx[i]);
  }
    return vals;
}

int main()
{
  const unsigned int nn =100;
  // {
  //   std::valarray<float> x(nn+1,0.);
  //   x = linspace(0., 1., nn );
  //   plot(x, f(x));
  // }

// auto params = linspace(-1,1, 10);
//   for(auto a : params)
  {
    std::valarray<float> x(nn+1,0.);
    x = linspace(0., 1., nn );
    // auto y = kernel_CubicConvolution(x);

  
    // auto sum = std::accumulate(std::begin(kernel_linear(x)),std::end(kernel_linear(x)),0,std::plus<float>());
    // std::cout << " sum " << sum << std::endl;
  
    // (&y)->begin();
    // plot(x, kernel_CubicConvolution(x));
    plot(x, kernel_linear(x));
  }


}
