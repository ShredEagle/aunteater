#ifndef _IDG_AE_Family
#define _IDG_AE_Family

#include "Entity.h"
#include "Handle.h"
#include "Node.h"

#include "globals.h"

#include <map>
#include <list>

namespace aunteater
{
    class Engine;
    
    class Family
    {
    private:
        // The implementation assumes that inserting/removing a Node from the collection does not invalidate any
        // existing iterator into the collection.
        typedef std::list<Node> NodeList;

    public:
        Family(Engine & aEngine, ArchetypeTypeSet aComponentsTypeInfo);
        
        std::list<Node> & getNodes()
        {
            return mNodes;
        }
        
        void testEntityInclusion(weak_entity aEntity);
        void removeIfPresent(weak_entity aEntity);

        void componentAddedToEntity(weak_entity aEntity, ComponentTypeId aComponent);
        void componentRemovedFromEntity(weak_entity aEntity, ComponentTypeId aComponent);

    private:
        void addIfMatch(weak_entity aEntity);
        
        bool isPresent(weak_entity aEntity) const;
        bool includesComponent(ComponentTypeId aComponent) const;
        
    private:
        Engine & mEngine;
        NodeList mNodes;
        ArchetypeTypeSet mComponentsTypeInfo;
        
        /// \note It works to use an iterator because we use a std::list
        /// for which operation on elements do not affect other iterators.
        
        // This map is usefull to test if an entity is present in the current family instance
        std::map<weak_entity, NodeList::iterator > mEntitiesToNodes;
    };
    
} // namespace aunteater

#endif  // #ifdef