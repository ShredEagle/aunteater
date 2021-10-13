#pragma once

#include "EntityManager.h"
#include "Timer.h"

namespace aunteater
{

class EntityManager;

template <class T_timer = Timer, class T_inputState = void>
class System
{
public:
    virtual void update(const T_timer aTime, const T_inputState & aInputState) = 0;
    virtual ~System() = default;
};

/// \brief Specialization when there are no input state provided for the update()
template <class T_timer>
class System<T_timer, void>
{
public:
    virtual void update(const T_timer aTime) = 0;
};

} // namespace aunteater
