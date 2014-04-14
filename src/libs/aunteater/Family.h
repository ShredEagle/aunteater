#ifndef _IDG_AE_Family
#define _IDG_AE_Family

#include "Entity.h"
#include "Handle.h"
#include "Node.h"

#include <set>
#include <list>
#include <typeinfo>
#include <memory>
#include <vector>

namespace aunteater
{
    class Engine;
    
    class Family
    {
    private:
        typedef std::list<Node> NodeList;

    public:
        Family(Engine & aEngine, ArchetypeTypeSet aComponentsTypeInfo);
        
        std::list<Node> & getNodes()
        {
            return mNodes;
        }
        
        void testEntityInclusion(Handle<Entity> aEntity);
        void removeIfPresent(Handle<Entity> aEntity);
        
    private:
        void addIfMatch(Handle<Entity> aEntity);
        
        void removeEntity(std::shared_ptr<Entity> aEntity);
        void componentAddedToEntity(std::shared_ptr<Entity> aEntity,std::type_info * aComponent);
        void componentRemovedFromEntity(std::shared_ptr<Entity> aEntity,std::type_info * aComponent);
        
    private:
        Engine & mEngine;
        NodeList mNodes;
        ArchetypeTypeSet mComponentsTypeInfo;
        
        /// \note It works to use an iterator because we use a std::list
        /// for which operation on elements do not affect other iterators.
        
        // This map is usefull to test if an entity is present in the current family instance
        std::map<Handle<Entity>, NodeList::iterator > mEntities;
    };
    
} // namespace aunteater

#endif  // #ifdef