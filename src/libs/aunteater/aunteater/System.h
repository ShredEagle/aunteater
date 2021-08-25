#pragma once

#include "EntityManager.h"
#include "Timer.h"

namespace aunteater
{

class EntityManager;

template <class T_inputState = void>
class System
{
public:
    virtual void update(const Timer aTime, const T_inputState & aInputState) = 0;
};

/// \brief Specialization when there are no input state provided for the update()
template <>
class System<void>
{
public:
    virtual void update(const Timer aTime) = 0;
};

} // namespace aunteater
