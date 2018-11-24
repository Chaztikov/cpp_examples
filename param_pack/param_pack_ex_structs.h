#include <iostream>
#include <string>
#include <vector>


// using namespace std;

template <typename T, typename... Args>
void push_back_vec(std::vector<T> &v, Args &&... args)
{
    (v.push_back(args), ...);
}

template <typename T, typename... Args>
void FoldWrite(
    std::ofstream &outfile,
    std::string &savename,
    Args &&... args)
{
    outfile.open(savename, std::ios_base::app);
    (outfile << ... << std::forward<Args>(args)) << "\n";
}

template<typename ...Args>
void FoldPrint(Args&&... args) {
    (std::cout <<  ... <<  std::forward<Args>(args)) << "\n";
}

template<typename T, typename... Args>
void FoldPushBack(std::vector<T>& v, Args&&... args)
{
    (v.push_back(args), ...);
}


 
template<typename ...Args> auto sum(Args ...args) 
{ 
    return (args + ... + 0); 
}

template<typename ...Args> auto sum2(Args ...args) 
{ 
    return (args + ...);
}

// int main()
// {
//     cout << sum(1, 2, 3, 4, 5, 6, 7) << "\n";
// 	cout << sum2(1, 2, 3, 4, 5, 6, 7) << "\n";
// }

