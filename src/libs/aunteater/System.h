#ifndef _IDG_AE_System
#define _IDG_AE_System

#include "Engine.h"

namespace aunteater
{
    
    class Engine;
    
    class System
    {
    public:
        virtual void addedToEngine(Engine &aEngine)=0;
        virtual void update(float time)=0;
        
    };
    
} // namespace aunteater

#endif  // #ifdef