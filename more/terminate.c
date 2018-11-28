#include <iostream>
#include <cstdlib>
#include <exception>
 
int main()
{
    std::set_terminate([](){ std::cout << "Unhandled exception\n"; std::abort();});
    throw 1;
}