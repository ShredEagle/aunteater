#pragma once

#include "Engine.h"

namespace aunteater
{

    class Engine;

    class System
    {
    public:
        virtual void addedToEngine(Engine &aEngine)=0;
        virtual void update(double aTime)=0;
    };

} // namespace aunteater
