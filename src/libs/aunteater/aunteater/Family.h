#pragma once

#include "Entity.h"
#include "Node.h"

#include "globals.h"

#include <map>
#include <list>
#include <vector>

namespace aunteater
{
    class Engine;

    class FamilyObserver
    {
    public:
        virtual void addedNode(Node &aNode) = 0;
        virtual void removedNode(Node &aNode) = 0;
    };

    // Review note: Should probably be non-copyable,
    // to avoid the risk of a component forgetting to take it by ref
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

        void addIfMatch(weak_entity aEntity);
        void removeIfPresent(entity_id aEntity);

        void componentAddedToEntity(weak_entity aEntity, ComponentTypeId aComponent);
        void componentRemovedFromEntity(entity_id aEntity, ComponentTypeId aComponent);

        Family & registerObserver(FamilyObserver *aObserver)
        {   mObservers.push_back(aObserver); notifyOfExistingNodes(aObserver); return *this;  }

        Family & cancelObserver(FamilyObserver *aObserver)
        {   cancelObserverImpl(aObserver); return *this;  }

    private:

        bool isPresent(entity_id aEntity) const;
        bool includesComponent(ComponentTypeId aComponent) const;

        typedef void (FamilyObserver::*NotificationMethod)(Node &);
        void broadcastNotification(NotificationMethod aTargetMethod, Node &aNode) const;
        void cancelObserverImpl(FamilyObserver *aObserver);
        void notifyOfExistingNodes(FamilyObserver *aObserver);

    private:
        Engine & mEngine;
        NodeList mNodes;
        ArchetypeTypeSet mComponentsTypeInfo;

        /// \note It works to use an iterator because we use a std::list
        /// for which operation on elements do not affect other iterators.

        // This map is usefull to test if an entity is present in the current family instance
        std::map<entity_id, NodeList::iterator> mEntitiesToNodes;

        std::vector<FamilyObserver *> mObservers;
    };

} // namespace aunteater
