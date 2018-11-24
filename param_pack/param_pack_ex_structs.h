#include <iostream>
#include <string>
#include <vector>


using namespace std;
 
template<typename ...Args>
void FoldPrint(Args&&... args) {
    (cout <<  ... <<  forward<Args>(args)) << '\n';
}

template<typename T, typename... Args>
void FoldPushBack(vector<T>& v, Args&&... args)
{
    (v.push_back(args), ...);
}

int main()
{
    FoldPrint("hello", ", ", 10, ", ", 90.0);

    vector<int> v;
	FoldPushBack(v, 1, 2, 3, 4);
	
	for (auto &i : v)
		cout << i << "\n";
}
