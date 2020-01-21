//
//  SystemRender.h
//
//  Created by Adrien David.
//
//

#ifndef BenchingBall_SystemRender_h
#define BenchingBall_SystemRender_h

#include <aunteater/System.h>

struct GLFWwindow;

namespace BenchingBall {

class SystemRender : public aunteater::System
{
public:
    SystemRender(GLFWwindow *aWindow) :
            mWindow(aWindow)
    {}

    /// \todo removedFromEngine, to be symetric
    virtual void addedToEngine(aunteater::Engine &aEngine) override;
    virtual void update(double time) override;

protected:
    void extendTransformBuffer(std::size_t aNewSize);
    void streamPositions();
    void render();

private:
    /// \todo make it easier to get those nodelist
    aunteater::EntityList * mRenderables;

    GLFWwindow *mWindow;
    std::size_t mTransformBufferSize = 0;
};

} // namespace BenchingBall

#endif
