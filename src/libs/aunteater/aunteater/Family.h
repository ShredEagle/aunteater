#pragma once

#include "Archetype.h"
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

        virtual ~FamilyObserver() = default;
    };


    // The implementation assumes that inserting/removing an Entity from the collection
    // does not invalidate any existing iterator into the collection.
    typedef std::list<weak_entity> EntityList;

    // Review note: Should probably be non-copyable,
    class Family
    {
        // Needs to call:
        // addIfMatch, removeIfPresent, componentAddedToEntity, componentRemovedFromEntity
        friend class Engine;
        // TODO Might not be useful anymore
        // Needs to call componentAddedTo(RemovedFrom)Entity
        friend class LiveEntity;

    public:
        // Note: must be accessible to pair forwarded constructor (cannot be private)
        explicit Family(ArchetypeTypeSet aComponentsTypeInfo);

        // Non-copyable, to avoid the risk of a component forgetting to take it by ref
        //
        // Implementer's note: aOther is *const* reference, otherwise it cannot be used in a pair
        // see https://stackoverflow.com/q/22357887/1027706
        // Yes, C++ requires you to delete the right signature
        Family(const Family & aOther) = delete;
        // TODO should not it be const too ??
        Family & operator=(Family & aOther) = delete;

        /// \brief Inteded for client use, not used as an internal mechanism
        Family & registerObserver(FamilyObserver *aObserver);
        Family & cancelObserver(FamilyObserver *aObserver);

        std::size_t size() const noexcept;

        auto begin() noexcept;
        auto begin() const noexcept;
        auto cbegin() const noexcept;

        auto end() noexcept;
        auto end() const noexcept;
        auto cend() const noexcept;

        EntityList::iterator find(entity_id aEntityId);
        EntityList::const_iterator find(entity_id aEntityId) const;

        /// \brief Returns a weak_entity if it is part of this family, nullptr otherwise
        /// \note This makes for an easy test in conditions
        weak_entity contains(entity_id aEntityId);

    private:
        void addIfMatch(weak_entity aEntity);
        void removeIfPresent(entity_id aEntity);

        void componentAddedToEntity(weak_entity aEntity, ComponentTypeId aComponent);
        void componentRemovedFromEntity(entity_id aEntity, ComponentTypeId aComponent);

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
        // Refactor with shared and weak ptrs ?
        std::vector<FamilyObserver *> mObservers;
    };


    /***
     * Implementations
     ***/
    inline std::size_t Family::size() const noexcept
    {
        return mEntities.size();
    }

    inline auto Family::begin() noexcept
    {
        return mEntities.begin();
    }

    inline auto Family::begin() const noexcept
    {
        return mEntities.cbegin();
    }

    inline auto Family::cbegin() const noexcept
    {
        return mEntities.cbegin();
    }

    inline auto Family::end() noexcept
    {
        return mEntities.end();
    }

    inline auto Family::end() const noexcept
    {
        return mEntities.cend();
    }

    inline auto Family::cend() const noexcept
    {
        return mEntities.cend();
    }

    inline EntityList::iterator Family::find(entity_id aEntityId)
    {
        auto found = mEntitiesPositions.find(aEntityId);
        return (found != mEntitiesPositions.end()) ? found->second
                                                   : end();
    }

    inline EntityList::const_iterator Family::find(entity_id aEntityId) const
    {
        auto found = mEntitiesPositions.find(aEntityId);
        return (found != mEntitiesPositions.end()) ? found->second
                                                   : end();
    }

    inline weak_entity Family::contains(entity_id aEntityId)
    {
        auto found = mEntitiesPositions.find(aEntityId);
        return (found != mEntitiesPositions.end()) ? *(found->second)
                                                   : nullptr;
    }

} // namespace aunteater
