

/*
NOTE :
By using functional value and custom function, we can perform operation by changing the operator ( or using different functional value) in this STL function.

Possible Application : It returns the result of accumulating init with the inner products of the pair formed by the elements of two ranges starting at first1 and first2.

1. It can be used to find sum of products of i th index of both arrays.
For Example:
Array 1 : 1 2 3 4
Array 2 : 10 20 30 40

Sum of products : 300

Explanation : 1 * 10 + 2 * 20 + 3 * 30 + 4 * 40 = 300

*/

// CPP program to illustrate 
// std :: inner_product 
#include <iostream> // std::cout 
#include <functional> // std::minus, std::divides 
#include <numeric> // std::inner_product 
  
// Custom funcitons 
int myaccumulator(int x, int y) 
{ 
    return x + y; 
} 
int myproduct(int x, int y) 
{ 
    return x * y; 
} 
  
// Driver code 
int main() 
{ 
    // The value which is added after 
    // finding inner_product b/w elements 
    int init = 0; 
    int series1[] = { 1, 2, 3, 4 }; 
    int series2[] = { 10, 20, 30, 40 }; 
    int n = sizeof(series1) / sizeof(series1[0]); 
  
    // Elements in series1 
    std::cout << "Array 1 :"; 
    for (int i = 0; i < n; i++) 
        std::cout << " " << series1[i]; 
    std::cout << "\n"; 
  
    // Elements in series2 
    std::cout << "Array 2 :"; 
    for (int i = 0; i < n; i++) 
        std::cout << " " << series2[i]; 
    std::cout << "\n\n"; 
  
    std::cout << "Sum of products : "; 
    std::cout << std::inner_product(series1, series1 + n, series2, init, 
                                    myaccumulator, myproduct); 
    std::cout << '\n'; 


    

    return 0; 
} 