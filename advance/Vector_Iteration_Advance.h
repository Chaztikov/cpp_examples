#include <vector>
#include <algorithm>
#include <functional>

// Typically, iterators are used to access elements of a container in linear fashion; however, with "random access iterators", it is possible to access any element in the same fashion as operator[].

// To access arbitrary elements in a vector vec, you can use the following:

vec.begin()                  // 1st
vec.begin()+1                // 2nd
// ...
vec.begin()+(i-1)            // ith
// ...
vec.begin()+(vec.size()-1)   // last
// The following is an example of a typical access pattern (earlier versions of C++):

int sum = 0;
using Iter = std::vector<int>::const_iterator;
for (Iter it = vec.begin(); it!=vec.end(); ++it) {
    sum += *it;
}
// The advantage of using iterator is that you can apply the same pattern with other containers:

sum = 0;
for (Iter it = lst.begin(); it!=lst.end(); ++it) {
    sum += *it;
}
// For this reason, it is really easy to create template code that will work the same regardless of the container type. Another advantage of iterators is that it doesn't assume the data is resident in memory; for example, one could create a forward iterator that can read data from an input stream, or that simply generates data on the fly (e.g. a range or random number generator).

// Another option using std::for_each and lambdas:

sum = 0;
std::for_each(vec.begin(), vec.end(), [&sum](int i) { sum += i; });
// Since C++11 you can use auto to avoid specifying a very long, complicated type name of the iterator as seen before (or even more complex):

sum = 0;
for (auto it = vec.begin(); it!=vec.end(); ++it) {
    sum += *it;
}
// And, in addition, there is a simpler for-each variant:

sum = 0;
for (auto value : vec) {
    sum += value;
}
// And finally there is also std::accumulate where you have to be careful whether you are adding integer or floating point numbers.



// Alternatively you can use the advance function which works with all kinds of iterators. (You'd have to consider whether you really want to perform "random access" with non-random-access iterators, since that might be an expensive thing to do.)

std::vector<int> vec(10);
std::vector<int>::iterator it = vec.begin();

std::advance(it, 5);
int sixth = *it;