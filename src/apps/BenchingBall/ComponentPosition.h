//
//  ComponentPosition.h
//
//  Created by Adrien David.
//
//

#ifndef BenchingBall_ComponentPosition_h
#define BenchingBall_ComponentPosition_h

#include "Vec2.h"

#include <aunteater/Component.h>

namespace BenchingBall {

struct ComponentPosition : public aunteater::Component, public Vec2
{
    ComponentPosition(double x, double y) : Vec2{x, y}
    {}

private:
    COMP_CLONE(ComponentPosition)
};

} // namespace BenchingBall

#endif
