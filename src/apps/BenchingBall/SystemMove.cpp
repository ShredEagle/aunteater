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



typedef ComponentPosition Position;
typedef ComponentVelocity Velocity;

void SystemMove::addedToEngine(aunteater::Engine &aEngine)
{
    mMoveables = & aEngine.getFamily<NodeMoveable>();
}

double impulse(const Vec2 &aNormal, const Vec2 &aSpeedA, const Vec2 &aSpeedB, double aMass)
{
    double eps = 1.;
    Vec2 vr = aSpeedB - aSpeedA; //Speed of B relative to A
    return -(1+eps) * vr.dot(aNormal) / (1/aMass + 1/aMass);
}

void collision(LiveEntity & A, LiveEntity & B)
{
    Vec2 normal = (B.get<Position>() - A.get<Position>()).normalize();
    double mass = 0.1;
    double J = impulse(normal, A.get<Velocity>(), B.get<Velocity>(), mass);

    static_cast<Vec2 &>(A.get<Velocity>()) = A.get<Velocity>() - normal * (J/mass);
    static_cast<Vec2 &>(B.get<Velocity>()) = B.get<Velocity>() + normal * (J/mass);

    double penetration = 2*RADIUS - distance(A.get<Position>(), B.get<Position>());
    static_cast<Vec2 &>(A.get<Position>()) -= normal*(penetration/2.);
    static_cast<Vec2 &>(B.get<Position>()) += normal*(penetration/2.);
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
        move(time, (*nodeIt)->get<ComponentPosition>().x, (*nodeIt)->get<ComponentVelocity>().x, RADIUS);
        move(time, (*nodeIt)->get<ComponentPosition>().y, (*nodeIt)->get<ComponentVelocity>().y, RADIUS);
    }


    for (auto nodeIt = mMoveables->begin();
         nodeIt != mMoveables->end();
         ++nodeIt)
    {
        for (auto nodeItB = ++decltype(nodeIt)(nodeIt);
             nodeItB != mMoveables->end();
             ++nodeItB)
        {
            if (distance((*nodeIt)->get<ComponentPosition>(), (*nodeItB)->get<ComponentPosition>()) < 2*RADIUS)
            {
                collision(**nodeIt, **nodeItB);
            }
        }
    }
}
