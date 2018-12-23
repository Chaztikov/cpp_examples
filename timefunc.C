// Just for convenience
using Seconds = std::chrono::duration<double>;

// Measure how much time the given function takes to execute using chrono
// Pass the function name, then all relevant arguments, including the object as the first if it's a member function

template<typename Function, typename... Args>
Seconds measure(Function&& toTime, Args&&... a)
{
    auto start{std::chrono::steady_clock::now()};                                                   // Start timer
    std::invoke(std::forward<Function>(toTime), std::forward<Args>(a)...);  // Forward and call
    auto stop{std::chrono::steady_clock::now()};                                                   // Stop timer
    return (stop - start);
}
