#include <iostream>
#include <string>
#include <vector>


using namespace std;
 
template<typename ...Args>
void FoldPrint(Args&&... args) {
    (cout <<  ... <<  forward<Args>(args)) << '\n';
}

// int main()
// {
//     FoldPrint("hello", ", ", 10, ", ", 90.0);
// }

template<typename T, typename... Args>
void FoldPushBack(vector<T>& v, Args&&... args)
{
    (v.push_back(args), ...);
}
// int main()
// {
//     vector<int> v;
// 	FoldPushBack(v, 1, 2, 3, 4);
	
// 	for (auto &i : v)
// 		cout << i << "\n";
// }


/*
 fold over a comma operator:
*/
template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args)
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

