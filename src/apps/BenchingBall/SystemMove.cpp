#include "SystemMove.h"

#include "ComponentPosition.h"
#include "ComponentVelocity.h"

#include "globals.h"

#include <aunteater/Engine.h>

using namespace BenchingBall;
using namespace aunteater;

class NodeMoveable
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeMoveable::gComponentTypes = { &typeid(ComponentPosition),
                                                         &typeid(ComponentVelocity) };



void SystemMove::addedToEngine(aunteater::Engine &aEngine)
{
    mMoveables = &aEngine.getNodes<NodeMoveable>();
}


void move(double aTime, double &aPosition, double &aVelocity, double aRadius)
{
    aPosition += aVelocity * aTime;
    double overflow = aVelocity > 0. ? std::max(1., aPosition + aRadius) - 1. :
                                       std::min(-1., aPosition - aRadius) + 1.;
    if (overflow) // not null, positive or negative
    {
        aPosition -= overflow;
        aVelocity *= -1;
    }
}

void SystemMove::update(double time)
{
   for (auto nodeIt = mMoveables->begin();
        nodeIt != mMoveables->end();
        ++nodeIt)
   {
       move(time, nodeIt->get<ComponentPosition>().x, nodeIt->get<ComponentVelocity>().x, RADIUS);
       move(time, nodeIt->get<ComponentPosition>().y, nodeIt->get<ComponentVelocity>().y, RADIUS);
   }
}