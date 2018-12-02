/*
https://stackoverflow.com/questions/50065712/mapping-objects-as-key-with-unordered-map
*/

#include <functional>
#include <unordered_map>
#include <map>
#include <vector>
#include <utility>

template <typename Event>
class Observable
{
public:
    Observable()=default;

    template <typename Observer>
    void registerObserver(const Event &event, Observer &&observer)
    {
        _observers[event].push_back(std::forward<Observer>(observer));
    }

    template <typename Observer>
    void registerObserver(Event &&event, Observer &&observer)
    {
        _observers[std::move(event)].push_back(std::forward<Observer>(observer));
    }

    void notify(const Event &event) const
    {
        for (const auto& obs : _observers.at(event)) obs();
    }

    /* disallow copying */
    Observable(const Observable&)=delete;
    Observable& operator=(const Observable&)=delete;

private:
    std::map<Event, std::vector<std::function<void()>>> _observers;
};