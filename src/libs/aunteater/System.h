#ifndef _IDG_AE_System
#define _IDG_AE_System

namespace aunteater
{
    
    class Engine;
    
    class System
    {
    public:
        virtual void addToEngine(Engine &aEngine) =0;
        
    };
    
} // namespace aunteater

#endif  // #ifdef