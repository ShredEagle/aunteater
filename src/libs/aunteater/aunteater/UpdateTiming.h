#pragma once

#include "Engine.h"
#include "System.h"

#include <boost/core/demangle.hpp>

#include <chrono>
#include <map>
#include <typeinfo>

namespace aunteater {

class UpdateTiming : public Engine
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

    void operator()(System & aSystem, const Timer aTime)
    {
        aSystem.update(aTime);
        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        mTimings.emplace(getTypeName(aSystem),
                         std::chrono::duration_cast<std::chrono::microseconds>(now - pre));
        pre = now;
    }

    void finish()
    {
        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        mTimings.emplace("Engine::removeEntities()",
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


inline void UpdateTiming::outputTimings(std::ostream &os) const
{
    for(auto timing : mTimings)
    {
        os << timing.first << ": " << timing.second.count() << "us\n";
    }
}

} // namespace aunteater
