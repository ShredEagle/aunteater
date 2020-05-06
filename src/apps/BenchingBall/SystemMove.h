//
//  SystemMove.h
//
//  Created by Adrien David.
//
//

#ifndef BenchingBall_SystemMove_h
#define BenchingBall_SystemMove_h

#include <aunteater/System.h>

namespace BenchingBall {

class SystemMove : public aunteater::System
{
public:
    SystemMove(aunteater::Engine &aEngine);
    virtual void update(const aunteater::Timer aTime) override;

private:
    /// \todo make it easier to get those nodelist
    aunteater::Family & mMoveables;
};

} // namespace BenchingBall

#endif
