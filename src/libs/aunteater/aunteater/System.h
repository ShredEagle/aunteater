#pragma once

#include "Engine.h"
#include "Timer.h"

namespace aunteater
{

    class Engine;

    class System
    {
    public:
        virtual void update(const Timer aTime)=0;
    };

} // namespace aunteater
