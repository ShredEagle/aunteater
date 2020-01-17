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

struct ComponentPosition : public aunteater::ComponentBase<ComponentPosition>, public Vec2
{
    ComponentPosition(double x, double y) : Vec2{x, y}
    {}
};

} // namespace BenchingBall

#endif
