#include <Polycode.h>


// Fuck you whales and fuck you Dolphin:
// Never have a technical job:
// Polycode cannot be built using libc++, because I did not find an easy way to build its dependencies
// with this version of the stdlib (so symbol resolution problems)
// Because of that, we cannot build our code with libc++
// and libstdc++ shipped by apple does not provide std::forward template, which is used by bimap
// so whe have this define, see :
// https://svn.boost.org/trac/boost/ticket/8092
#define BOOST_NO_CXX11_RVALUE_REFERENCES
#include <aunteater/Engine.h>

#include "Factories.h"

#include "ComponentSprite.h"

#include "SystemDisplay.h"
#include "SystemMove.h"
#include "InputSystem.h"
#include "SystemAnimation.h"
#include "SystemMoveAnimation.h"
#include "SystemScaling.h"
#include "SystemCollision.h"

#include <memory>


class HardCore
{
public:
    HardCore(Polycode::Core *aCore):
            mCore(aCore),
            mScreen(new Polycode::Screen())
    {
        
    }
    
	void init();
   
    bool update()
    {
        Number elapsed = mCore->getElapsed();
		mEngine.update(elapsed);
        return mCore->updateAndRender();
    }
    
private:
    Polycode::Screen *mScreen;
    Polycode::ScreenImage *image;
    Polycode::Core * mCore;
    aunteater::Engine mEngine;
};
/*
Polycode::Core * hardCore(Polycode::Core *core)
{
//	CoreServices::getInstance()->getResourceManager()->addArchive("/Users/adn/projects/SDK/polycode/Framework/Examples/Darwin/Resources/default.pak");
//	CoreServices::getInstance()->getResourceManager()->addDirResource("/Users/adn/projects/SDK/polycode/Framework/Examples/Darwin/Resources", false);


    
    return core;
}
*/