#ifndef _IDG_AE_Family
#define _IDG_AE_Family

#include "Node.h"

#include <set>
#include <list>
#include <typeinfo>
#include <memory>
namespace aunteater
{
    class Entity;
    class Engine;
    
    class Family
    {
    private:
        Engine & mEngine;
        std::list<Node> mNodes;
        ComponentIds mComponentsTypeInfo;
        
        std::set<std::shared_ptr<Entity> > mEntities; // ?
    public:
        Family(Engine & aEngine, ComponentIds aComponentsTypeInfo);
        
        std::list<Node> & getNodes()
        {
            return mNodes;
        }
        
        void testEntityInclusion(Entity &aEntity);
        
    private:
        void addIfMatch(Entity &aEntity);
        
        void removeEntity(std::shared_ptr<Entity> aEntity);
        void componentAddedToEntity(std::shared_ptr<Entity> aEntity,std::type_info * aComponent);
        void componentRemovedFromEntity(std::shared_ptr<Entity> aEntity,std::type_info * aComponent);
        void removeIfMatch(std::shared_ptr<Entity> aEntity);
    };
    
} // namespace aunteater

#endif  // #ifdef