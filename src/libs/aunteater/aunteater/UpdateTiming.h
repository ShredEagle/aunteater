#pragma once

#include "System.h"
#include "aunteater/Timer.h"

#include <boost/core/demangle.hpp>

#include <chrono>
#include <map>
#include <ostream>
#include <typeinfo>

namespace aunteater {

template <class T_timer = Timer, class ... VT_inputState>
class UpdateTiming
{
    template <class T>
    std::string getTypeName(const T & aObject)
    {
        return boost::core::demangle(typeid(aObject).name());
    }

public:
    void start()
    {
        pre = initial = std::chrono::steady_clock::now();
    }

    void operator()(System<T_timer, VT_inputState...> & aSystem, const T_timer aTime, const VT_inputState & ... aInputState)
    {
        aSystem.update(aTime, aInputState...);
        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        mTimings.emplace(getTypeName(aSystem),
                         std::chrono::duration_cast<std::chrono::microseconds>(now - pre));
        pre = now;
    }

    void finish()
    {
        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        mTimings.emplace("EntityManager::removeEntities()",
                         std::chrono::duration_cast<std::chrono::microseconds>(now - pre));

        mTimings.emplace("Update Total",
                         std::chrono::duration_cast<std::chrono::microseconds>(now - initial));
    }

    void outputTimings(std::ostream &os) const;

private:
    std::chrono::steady_clock::time_point initial;
    std::chrono::steady_clock::time_point pre;

    std::map<std::string, std::chrono::microseconds> mTimings;
};


template <class T_timer, class ... VT_inputState>
void UpdateTiming<T_timer, VT_inputState...>::outputTimings(std::ostream &os) const
{
    for(auto timing : mTimings)
    {
        os << timing.first << ": " << timing.second.count() << "us\n";
    }
}

} // namespace aunteater
