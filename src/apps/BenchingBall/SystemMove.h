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
    /// \todo removedFromEngine, to be symetric
    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double time) override;

private:
    /// \todo make it easier to get those nodelist
    /// \todo should get rid of the useless pre-init state where the pointer is null
    aunteater::Family * mMoveables{nullptr};
};

} // namespace BenchingBall

#endif
