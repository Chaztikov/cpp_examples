
// CPP program to illustrate 
// std :: inner_product 
#include <iostream> // std::cout 
#include <functional> // std::minus, std::divides 
#include <numeric> // std::inner_product 


/*
https://www.geeksforgeeks.org/std-inner_product-in-cpp/
 *
 *
 *Template :
T inner_product (InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, T init);

Parameters :

first1, last1
Input iterators to the initial and final positions in the first
sequence.

first2
Input iterator to the initial position in the second sequence.
The range starts at first2 and has as many elements as the range
above [first1, last1].

init
Initial value for the accumulator.

Neither operations shall modify any of the elements passed as
its arguments.

Return Type :
The result of accumulating init and the products of all the pairs
of elements in the ranges starting at first1 and first2.
 *
 *
 *
 * */  
// Driver code 
int main() 
{ 
    // The value which is added after 
    // finding inner_product b/w elements 
    int init = 100; 
    int series1[] = { 10, 20, 30 }; 
    int series2[] = { 1, 2, 3 }; 
    int n = sizeof(series1) / sizeof(series1[0]); 
  
    // Elements in series1 
    std::cout << "First array contains :"; 
    for (int i = 0; i < n; i++) 
        std::cout << " " << series1[i]; 
    std::cout << "\n"; 
  
    // Elements in series2 
    std::cout << "Second array contains :"; 
    for (int i = 0; i < n; i++) 
        std::cout << " " << series2[i]; 
    std::cout << "\n\n"; 
  
    std::cout << "Using default inner_product: "; 
    std::cout << std::inner_product(series1, series1 + n, series2, init); 
    std::cout << '\n'; 
  
    return 0; 
} 
