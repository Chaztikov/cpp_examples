#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <experimental/execution>
int main()
{
    std::string path = std::experimental::filesystem::current_path();

    std::cout << "path = " << path << std::endl;
}

