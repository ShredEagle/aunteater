//
//  ComponentPosition.h
//
//  Created by Adrien David.
//
//

#ifndef BenchingBall_ComponentPosition_h
#define BenchingBall_ComponentPosition_h

#include <aunteater/Component.h>

namespace BenchingBall {

struct ComponentPosition : public aunteater::Component
{
    ComponentPosition(double x, double y) :
            x(x),
            y(y)
    {}

    double x;
    double y;

private:
    COMP_CLONE(ComponentPosition)
};

} // namespace BenchingBall

#endif
