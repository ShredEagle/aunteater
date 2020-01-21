#pragma once

#include "Entity.h"

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
        virtual void addedEntity(LiveEntity &aEntity) = 0;
        virtual void removedEntity(LiveEntity &aEntity) = 0;
    };


    // The implementation assumes that inserting/removing an Entity from the collection
    // does not invalidate any existing iterator into the collection.
    typedef std::list<weak_entity> EntityList;

    // Review note: Should probably be non-copyable,
    class Family
    {
    public:
        explicit Family(ArchetypeTypeSet aComponentsTypeInfo);

        // Non-copyable, to avoid the risk of a component forgetting to take it by ref
        //
        // Implementer's note: aOther is *const* reference, otherwise it cannot be used in a pair
        // see https://stackoverflow.com/q/22357887/1027706
        // Yes, C++ requires you to delete the right signature
        Family(const Family & aOther) = delete;
        Family & operator=(Family & aOther) = delete;

        // TODO delete
        //  When doing so, the systems should  then directly keep a reference to the family
        //  Work has to be done so it is more convenient to consume Families from Systems
        EntityList & getEntities()
        {
            return mEntities;
        }

        void addIfMatch(weak_entity aEntity);
        void removeIfPresent(entity_id aEntity);

        void componentAddedToEntity(weak_entity aEntity, ComponentTypeId aComponent);
        void componentRemovedFromEntity(entity_id aEntity, ComponentTypeId aComponent);

        Family & registerObserver(FamilyObserver *aObserver);
        Family & cancelObserver(FamilyObserver *aObserver);

    private:

        bool isPresent(entity_id aEntity) const;
        bool includesComponent(ComponentTypeId aComponent) const;

        typedef void (FamilyObserver::*NotificationMethod)(LiveEntity &);
        void broadcastNotification(NotificationMethod aTargetMethod, LiveEntity & aEntity) const;
        void cancelObserverImpl(FamilyObserver *aObserver);
        void notifyOfExistingEntities(FamilyObserver *aObserver);

    private:
        EntityList mEntities;
        ArchetypeTypeSet mComponentsTypeInfo;

        // Note: This map is usefull to test if an entity is present in the current family instance
        //       It works to use an iterator because for an std::list
        //       operations on an element do not affect other iterators.
        std::map<entity_id, EntityList::iterator> mEntitiesPositions;

        // TODO This is unsafe, if an observer expires without removing itself
        std::vector<FamilyObserver *> mObservers;
    };

} // namespace aunteater
