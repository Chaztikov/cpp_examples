#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/sort.h>
#include <thrust/copy.h>
#include <algorithm>
#include <cstdlib>

// REDUCE
/*
template<class InputIt>
typename std::iterator_traits<InputIt>::value_type reduce(
    InputIt first, InputIt last);

template<class ExecutionPolicy, class ForwardIt>
typename std::iterator_traits<ForwardIt>::value_type reduce(
    ExecutionPolicy&& policy,
    ForwardIt first, ForwardIt last);

template<class InputIt, class T>
T reduce(InputIt first, InputIt last, T init);

template<class ExecutionPolicy, class ForwardIt, class T>
T reduce(ExecutionPolicy&& policy,
         ForwardIt first, ForwardIt last, T init);

template<class InputIt, class T, class BinaryOp>
T reduce(InputIt first, InputIt last, T init, BinaryOp binary_op);

template<class ExecutionPolicy, class ForwardIt, class T, class BinaryOp>
T reduce(ExecutionPolicy&& policy,
         ForwardIt first, ForwardIt last, T init, BinaryOp binary_op);
The differences here are:

You can optionally provide an execution policy.
reduce is overloaded for input iterators and forward iterators.
Supplying the initial element is optional (default construction of the value type is used by default).
I’ll talk about these points in turn.

Execution policies
Execution policies are a C++17 feature which allows programmers to ask for algorithms to be parallelised. There are three execution policies in C++17:

std::execution::seq – do not parallelise
std::execution::par – parallelise
std::execution::par_unseq – parallelise and vectorise (requires that the operation can be interleaved, so no acquiring mutexes and such)
The idea behind execution policies is that you can change a serial algorithm to a parallel algorithm simply by passing an additional argument to the function:

auto sum1 = std::reduce(begin(vec), end(vec));                      //sequential
auto sum2 = std::reduce(std::execution::seq, begin(vec), end(vec)); //sequential
auto sum3 = std::reduce(std::execution::par, begin(vec), end(vec)); //parallel
*/
int main(void)
{

  return 0;
}

