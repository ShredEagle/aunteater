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


class HardCore
{
public:
    HardCore(Polycode::Core *aCore):
            mCore(aCore),
            mScreen(new Polycode::Screen())
    {
        
    }
    
    void init()
    {
        mEngine.addEntity("player", createPlayer(mScreen));
        
//        for(Number i=0; i < 20; i++)
//        {
//            image = new Polycode::ScreenImage("/Users/adn/GDJ/sprites/imgres.png");
//            mScreen->addChild(image);
//            image->setPosition(160+(42*i), 230);
//            image->setPositionMode(Polycode::ScreenEntity::POSITION_CENTER);
//            image->setRotation(45*i);
//            image->setScale(1.0-(0.1*i),1.0-(0.1*i));
//        }
    }
   
    bool update()
    {
        Number elapsed = mCore->getElapsed();
  //      image->setRotation(image->getRotation()+(elapsed*100));
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