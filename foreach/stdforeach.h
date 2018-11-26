#include <vector>
#include <algorithm>
#include <iostream>
 
struct Sum
{
    Sum(): sum{0} { }
    void operator()(int n) { sum += n; }
    int sum;
};
 
int main()
{
    std::vector<int> nums{3, 4, 2, 8, 15, 267};
 
    auto print = [](const int& n) { std::cout << " " << n; };
 
    std::cout << "before:";
    std::for_each(nums.begin(), nums.end(), print);
    std::cout << '\n';
 
    std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });
 
    // calls Sum::operator() for each number
    Sum s = std::for_each(nums.begin(), nums.end(), Sum());
 
    std::cout << "after: ";
    std::for_each(nums.begin(), nums.end(), print);
    std::cout << '\n';
    std::cout << "sum: " << s.sum << '\n';
}


/* 
fill NumericVector with element centroids
then apply std::transform to apply exact solution at every point 
 */
    // mesh.elements_begin()
    // mesh.elements_end()
    // std::advance(n,)
    // for(auto elem : mesh.element_ptr_range())
    // {
        
    // }
    // std::string s("hello");
    // std::transform(exact_scalarfield_elem.begin(), exact_scalarfield_elem.end(), exact_scalarfield_elem.begin(),
    //                [](unsigned char c) -> unsigned char { return std::toupper(c); });
    // exact_scalarfield_elem
    // exact_scalarfield_elem
    // std::generate( exact_scalarfield_elem->begin(), exact_scalarfield_elem->end(), [n = 0] () mutable { return n++; });