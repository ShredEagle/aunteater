//
//  ComponentVelocity.h
//
//  Created by Adrien David.
//
//

#ifndef BenchingBall_ComponentVelocity_h
#define BenchingBall_ComponentVelocity_h

#include <aunteater/Component.h>

namespace BenchingBall {

struct ComponentVelocity : public aunteater::Component
{
    ComponentVelocity(double x, double y) :
            x(x),
            y(y)
    {}

    double x;
    double y;

private:
    COMP_CLONE(ComponentVelocity)
};

} // namespace BenchingBall

#endif
