#ifndef _IDG_AE_Engine
#define _IDG_AE_Engine

#include "Entity.h"
#include "Handle.h"

#include <boost/bimap.hpp>

#include <map>
#include <string>
#include <vector>

namespace aunteater
{
    
    class Engine
    {
    public:
        Handle<Entity> addEntity(Entity aEntity);
        Handle<Entity> addEntity(const std::string & aName, Entity aEntity);
        
        void removeEntity(Handle<Entity> aId);
        
    private:
        std::vector<Entity> mEntities;
        typedef boost::bimap<std::string, Handle<Entity> > bmtype;
        boost::bimap<std::string, Handle<Entity> > mNamedEntities;
    };
    
} // namespace aunteater

#endif  // #ifdef