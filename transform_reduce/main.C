#include <vector>
#include <functional>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <experimental/filesystem>
#include <execution>
//#include <execution>
#include "/usr/lib/llvm-8/include/clang/Tooling/Execution.h"
//#include <experimental/execution_policy>
#include <chrono>
// #include </usr/include/leatherman/execution/execution.hpp>
//using namespace std::execution;

int main()
{
    std::vector<double> xvalues(10007, 1.0), yvalues(10007, 1.0);
 
 /**/
    double result = std::transform_reduce(
        std::execution::par,
        xvalues.begin(), xvalues.end(),
        yvalues.begin(), 0.0
    );
    std::cout << result << '\n';



    std::vector<double> v(10'000'007, 0.5);

 /**/
    {
        auto t1 = std::chrono::high_resolution_clock::now();

        double result = std::accumulate(v.begin(), v.end(), 0.0);

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout << std::fixed << "std::accumulate result " << result
                  << " took " << ms.count() << " ms\n";
    }
 

 /**/
    {
        auto t1 = std::chrono::high_resolution_clock::now();

        double result = std::reduce(std::execution::par, v.begin(), v.end());

        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout << "std::reduce result "
                  << result << " took " << ms.count() << " ms\n";
    }


/*
*/
    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) -> unsigned char { return std::toupper(c); });
 
    std::vector<std::size_t> ordinals;
    std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
                   [](unsigned char c) -> std::size_t { return c; });
 
    std::cout << s << ':';
    for (auto ord : ordinals) {
       std::cout << ' ' << ord;
    }

}

    std::vector<double> xvalues(10007, 1.0), yvalues(10007, 1.0);
    double result = std::transform_reduce(
        std::execution::par,
        xvalues.begin(), xvalues.end(),
        yvalues.begin(), , std::back_inserter(ordinals),
                   [](unsigned char c) -> std::size_t { return c; });
    std::cout << result << '\n';

