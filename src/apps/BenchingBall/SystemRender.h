//
//  SystemRender.h
//
//  Created by Adrien David.
//
//

#ifndef BenchingBall_SystemRender_h
#define BenchingBall_SystemRender_h

#include <aunteater/Archetype.h>
#include <aunteater/System.h>

struct GLFWwindow;

namespace BenchingBall {

typedef aunteater::Archetype<ComponentPosition> NodeRenderable;

class SystemRender : public aunteater::System
{
public:
    SystemRender(aunteater::Engine &aEngine, GLFWwindow *aWindow) :
            mRenderables(aEngine.getFamily<NodeRenderable>()),
            mWindow(aWindow)
    {}

    virtual void update(double time) override;

protected:
    void extendTransformBuffer(std::size_t aNewSize);
    void streamPositions();
    void render();

private:
    /// \todo make it easier to get those nodelist
    aunteater::Family & mRenderables;

    GLFWwindow *mWindow;
    std::size_t mTransformBufferSize = 0;
};

} // namespace BenchingBall

#endif
