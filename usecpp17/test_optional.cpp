//https://solarianprogrammer.com/2017/12/13/linux-wsl-install-clang-libcpp-compile-cpp-17-programs/
//
// C++17 optional test.
// You can compile the code with:
// clang++ -std=c++17 -stdlib=libc++ -Wall -pedantic test_optional.cpp -o test_optional
#include <iostream>
#include <optional>
#include <filesystem> 
 void show_optional_value(const std::optional<int> &o) {
     // Print the optional has a value if it is not empty
     if(o) {
         std::cout << "Optional value is: " << *o << '\n';
     } else {
         std::cout << "Optional is empty\n";
     }
 }
 int main() {
	 for(auto &file : std::filesystem::recursive_directory_iterator("./")) {
6         std::cout << file.path() << '\n';
     // Create an empty optional
     std::optional<int> o1;
 
     // Show the optional value
     show_optional_value(o1);
 
     // Store a value in the above optional variable
     o1 = -33;
 
     // Show the optional value
     show_optional_value(o1);
 }
