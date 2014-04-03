#ifndef _IDG_AE_Family
#define _IDG_AE_Family

#include "Node.h"

#include <set>
#include <list>
#include <typeinfo>
namespace aunteater
{
    class Entity;
    
    class Family
    {
    private:
        std::list<Node> mNodes;
        std::set<std::type_info> mComponentsTypeInfo;
        std::set<std::shared_ptr<Entity> > mEntities;
        Engine & mEngine;
    public:
        Family(Engine & aEngine, std::set<std::type_info> aComponentsTypeInfo):
        mEngine(aEngine),
        mComponentsTypeInfo(aComponentsTypeInfo)
        {
            
        }
        
        std::list<Node> & getNodes()
        {
            return mNodes;
        }
        
        void addEntity(std::shared_ptr<Entity> aEntity);
        void removeEntity(std::shared_ptr<Entity> aEntity);
        void componentAddedToEntity(std::shared_ptr<Entity> aEntity,std::type_info * aComponent);
        void componentRemovedFromEntity(std::shared_ptr<Entity> aEntity,std::type_info * aComponent);
    };
    
} // namespace aunteater

#endif  // #ifdef