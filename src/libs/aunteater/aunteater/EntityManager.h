#pragma once

#include "Entity.h"
#include "Family.h"

#include "globals.h"

#include <boost/bimap.hpp>

#include <map>
#include <string>

namespace aunteater
{


struct EntityManagerTag
{
private:
    friend class EntityManager;
    EntityManagerTag() = default;
};

/// \brief LiveEntity class
class LiveEntity
{
    friend class Family;
    friend class EntityManager; // accesses remove_impl

    // Non-copiable, non-movable
    LiveEntity(const LiveEntity&) = delete;
    LiveEntity & operator=(const LiveEntity&) = delete;

public:
    // Note: Only constructible by EntityManager
    LiveEntity(Entity aEntity, EntityManager & aEntityManager, EntityManagerTag) :
        mEntity(std::move(aEntity)),
        mEntityManager(aEntityManager)
    {}

    /// \brief Return an Entity value by copying the wrapped entity
    explicit operator Entity()
    {
        return mEntity;
    }

    template <class T_component, class... Args>
    LiveEntity & add(Args&&... aArgs);

    /// \brief Removes the component of type T_component from this Entity.
    template <class T_component>
    LiveEntity & markComponentToRemove();

    template <class T_component>
    bool has()
    {
        return mEntity.has<T_component>();
    }

    template <class T_component>
    T_component & get()
    {
        return mEntity.get<T_component>();
    }

    template <class T_component>
    const T_component & get() const
    {
        return mEntity.get<T_component>();
    }

    void markToRemove();

private:
    void remove_impl(ComponentTypeId aId)
    {
        mEntity.remove_impl(aId);
    }

    /// \deprecated Currently required for Family inclusion test
    bool has(ComponentTypeId aId)
    {
        return mEntity.has(aId);
    }

private:
    Entity mEntity;
    EntityManager &mEntityManager;
};

class EntityManager
{
    template <class...>
    friend class SystemManager;

    // The entityManager register its address to the Entities added to it: it cannot have copy/move semantic.
    EntityManager(const EntityManager&) = delete;
    EntityManager & operator=(const EntityManager&) = delete;

public:
    /*
     * Construction
     */
    EntityManager() = default;

    /*
     * Entities manipulation
     */
    weak_entity addEntity(Entity aEntity);
    weak_entity addEntity(const std::string & aName, Entity aEntity);

    void markToRemove(weak_entity aEntity)
    {
        mEntitiesToRemove.emplace(aEntity);
    }

    void markToRemove(const std::string & aEntityName)
    {
        markToRemove(getEntity(aEntityName));
    }

    template <class T_component>
    void markComponentToRemove(weak_entity aEntity)
    {
        mComponentsToRemove.emplace(aEntity, type<T_component>());
    }

    weak_entity getEntity(const std::string & aEntityName)
    {
        return mNamedEntities.left.find(aEntityName)->second;
    }

    std::size_t countEntities() const
    {
        return mEntities.size();
    }

    /*
     * Families
     */
    template <class T_archetype>
    Family & getFamily();

    void forEachFamily(std::function<void(Family &aFamily)> aFamilyFunctor)
    {
        for (auto &typedFamily : mTypedFamilies)
        {
            aFamilyFunctor(typedFamily.second);
        }
    }

protected:
    void removeComponents();
    void removeEntities();
    void notifyAdditionToFamilies(weak_entity aEntity);
    void notifyRemovalToFamilies(entity_id aEntity);

private:
    typedef boost::bimap<std::string, weak_entity > NameEntityMap;
    typedef std::map<ArchetypeTypeId, Family> ArchetypeFamilyMap;

    std::list<LiveEntity> mEntities;
    NameEntityMap mNamedEntities;
    std::set<weak_entity> mEntitiesToRemove;
    std::set<std::pair<weak_entity, ComponentTypeId>> mComponentsToRemove;
    ArchetypeFamilyMap mTypedFamilies;
};


/*
 * Implementations
 */

inline void LiveEntity::markToRemove()
{
    mEntityManager.markToRemove(this);
}

template <class T_component>
LiveEntity & LiveEntity::markComponentToRemove()
{
    mEntityManager.markComponentToRemove<T_component>(this);
    return *this;
}

template <class T_component, class... Args>
LiveEntity & LiveEntity::add(Args&&... aArgs)
{
    mEntity.add<T_component>(std::forward<Args>(aArgs)...);

    // Note: does not test if insertion actually took place (return value from addComponent())
    //       It is expected to be rare to replace a component this way, so avoid branching
    //       (i.e. always iterate all families, not necessary in the rare replace situation)
    mEntityManager.forEachFamily([this](Family &family)
    {
       family.componentAddedToEntity(this, type<T_component>());
    });
    return *this;
}

template <class T_archetype>
Family & EntityManager::getFamily()
{
    auto insertionResult = mTypedFamilies.emplace(archetypeTypeId<T_archetype>(),
                                                  T_archetype::TypeSet());
    if (insertionResult.second)
    {
        Family &familyRef = insertionResult.first->second;
        for (LiveEntity & entity : mEntities)
        {
            familyRef.addIfMatch(entityRefFrom(entity));
        }
    }
    return insertionResult.first->second;
}


} // namespace aunteater
