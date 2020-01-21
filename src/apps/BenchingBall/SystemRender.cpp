#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "ComponentPosition.h"

#include "SystemRender.h"

#include "globals.h"

#include <aunteater/Engine.h>

using namespace BenchingBall;
using namespace aunteater;

class NodeRenderable
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet NodeRenderable::gComponentTypes = { &typeid(ComponentPosition) };

void SystemRender::addedToEngine(aunteater::Engine &aEngine)
{
    mRenderables = & aEngine.getEntities<NodeRenderable>();
}

void SystemRender::update(double time)
{
    streamPositions();
    render();
}

void SystemRender::streamPositions()
{
    if (mTransformBufferSize <= mRenderables->size()) // reassign a buffer
    {
        extendTransformBuffer(mRenderables->size());
    }

    GLfloat *transforms = static_cast<GLfloat *>(glMapBufferRange(GL_ARRAY_BUFFER, 0,
                                                                  mTransformBufferSize*9*sizeof(GLfloat), GL_MAP_WRITE_BIT));
    std::size_t ballId = 0;
    for (auto nodeIt = mRenderables->begin();
         nodeIt != mRenderables->end();
         ++nodeIt, ++ballId)
    {
        transforms[ballId*9 + 6] = (*nodeIt)->get<ComponentPosition>()->x;
        transforms[ballId*9 + 7] = (*nodeIt)->get<ComponentPosition>()->y;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void SystemRender::extendTransformBuffer(std::size_t aNewSize)
{
    glBufferData(GL_ARRAY_BUFFER, aNewSize*9*sizeof(GLfloat), nullptr, GL_STREAM_DRAW);
    GLfloat *transforms = static_cast<GLfloat *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    for(std::size_t ballId = 0; ballId != aNewSize; ++ballId)
    {
        for(auto i : {0, 1, 2})
        {
            for(auto j : {0, 1, 2})
            {
                transforms[ballId*9 + i*3+j] = (i==j) ? 1.f : 0.f;
            }
        }
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    mTransformBufferSize = aNewSize;
}

void SystemRender::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, SMOOTH, mTransformBufferSize);
    glfwSwapBuffers(mWindow);
}
