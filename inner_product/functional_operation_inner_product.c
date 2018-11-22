/*
Template :
T inner_product (InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, T init,
                 BinaryOperation1 binary_op1,
                 BinaryOperation2 binary_op2);

Parameters :

first1, last1, first2, init are same as above.

binary_op1
Binary operation taking two elements of type T as arguments, and
returning the result of an accumulation operation.
This can either be a function pointer or a function object.

binary_op2
Binary operation taking two elements of type T as arguments, and
returning the result of the inner product operation.
This can either be a function pointer or a function object.

Here binary_op1 and binary_op2 are functional operation.

Neither operations shall modify any of the elements passed as
its arguments.

Return Type :
The result of accumulating init and the products of all the pairs
of elements in the ranges starting at first1 and first2.

*/
// CPP program to illustrate 
// std :: inner_product 
#include <iostream> // std::cout 
#include <functional> // std::minus, std::divides 
#include <numeric> // std::inner_product 
  
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
  
    std::cout << "Using functional operations: "; 
    // std :: minus returns the difference b/w 
    // each elements of both array 
    // std :: divides return the quotient of 
    // each elements of both array after performing 
    // divide operation 
    // The operations is performed b/w number of same index 
    // of both array 
    std::cout << std::inner_product(series1, series1 + n, series2, init, 
                                    std::minus<int>(), std::divides<int>()); 
    std::cout << '\n'; 
  
    return 0; 
} 