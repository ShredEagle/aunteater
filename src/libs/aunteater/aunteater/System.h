#pragma once

#include "EntityManager.h"
#include "Timer.h"

namespace aunteater
{

    class EntityManager;

    class System
    {
    public:
        virtual void update(const Timer aTime)=0;
    };

} // namespace aunteater
