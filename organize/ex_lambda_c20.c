
// https://en.cppreference.com/w/cpp/language/lambda

{
	// generic lambda, operator() is a template with two parameters
	auto glambda = [](auto a, auto&& b) { return a < b; };
	bool b = glambda(3, 3.14); // ok
	 
	// generic lambda, operator() is a template with one parameter
	auto vglambda = [](auto printer) {
	    return [=](auto&&... ts) // generic lambda, ts is a parameter pack
	    { 
	        printer(std::forward<decltype(ts)>(ts)...);
	        return [=] { printer(ts...); }; // nullary lambda (takes no parameters)
	    };
	};
	auto p = vglambda([](auto v1, auto v2, auto v3) { std::cout << v1 << v2 << v3; });
	auto q = p(1, 'a', 3.14); // outputs 1a3.14
	q();                      // outputs 1a3.14
}




{

	struct X {
	    int x, y;
	    int operator()(int);
	    void f()
	    {
	        // the context of the following lambda is the member function X::f
	        [=]()->int
	        {
	            return operator()(this->x + y); // X::operator()(this->x + (*this).y)
	                                            // this has type X*
	        };
	    }
	};

}


{
	// generic lambda, operator() is a template with two parameters
	auto glambda = []<class T>(T a, auto&& b) { return a < b; };
	 
	// generic lambda, operator() is a template with one parameter pack
	auto f = []<typename ...Ts>(Ts&& ...ts) {
	   return foo(std::forward<Ts>(ts)...);
	};
}


#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
 
int main()
{
    std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};
    int x = 5;
    c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());
 
    std::cout << "c: ";
    std::for_each(c.begin(), c.end(), [](int i){ std::cout << i << ' '; });
    std::cout << '\n';
 
    // the type of a closure cannot be named, but can be inferred with auto
    // since C++14, lambda could own default arguments
    auto func1 = [](int i = 6) { return i + 4; };
    std::cout << "func1: " << func1() << func1() << '\n';
 
    // like all callable objects, closures can be captured in std::function
    // (this may incur unnecessary overhead)
    std::function<int(int)> func2 = [](int i) { return i + 4; };
    std::cout << "func2: " << func2(6) << '\n';
}


    // generic lambda, operator() is a template with two parameters
    auto lambda_accumulator = []<class T>(T a, auto&& b) { return a < b; };
     
    // generic lambda, operator() is a template with one parameter pack
    auto lambda_product = []<typename ...Ts>(Ts&& ...ts) {
       return foo(std::forward<Ts>(ts)...);
