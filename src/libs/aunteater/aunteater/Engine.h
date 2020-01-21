#pragma once

#include "Entity.h"
#include "Family.h"

#include "globals.h"

#include <boost/bimap.hpp>

#include <map>
#include <string>
#include <vector>

namespace aunteater
{


struct EngineTag
{
private:
    friend class Engine;
    EngineTag() = default;
};

/// \brief LiveEntity class
class LiveEntity
{
    friend class Family;

    // Non-copiable, non-movable
    LiveEntity(const LiveEntity&) = delete;
    LiveEntity & operator=(const LiveEntity&) = delete;

public:
    // Note: Only constructible by Engine
    LiveEntity(Entity aEntity, Engine & aEngine, EngineTag) :
        mEntity(std::move(aEntity)),
        mEngine(aEngine)
    {}

    /// \brief Return an Entity value by copying the wrapped entity
    explicit operator Entity()
    {
        return mEntity;
    }

    template <class T_component, class... Args>
    LiveEntity & addComponent(Args&&... aArgs);

    /// \brief Removes the component of type T_component from this Entity.
    template <class T_component>
    LiveEntity & removeComponent();

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

    /// TODO remove!
    Component & get(ComponentTypeId aId)
    {
        return mEntity.get(aId);
    }

    template <class T_component>
    const T_component & get() const
    {
        return mEntity.get<T_component>();
    }

private:

    /// \deprecated Currently required for Family inclusion test
    bool has(ComponentTypeId aId)
    {
        return mEntity.has(aId);
    }

private:
    Entity mEntity;
    Engine &mEngine;
};

class Engine
{
    // The engine register its address to the Entities added to it: it cannot have copy/move semantic.
    Engine(const Engine&) = delete;
    Engine & operator=(const Engine&) = delete;

public:
    /*
     * Construction
     */
    Engine() = default;

    /*
     * Entities manipulation
     */
    weak_entity addEntity(Entity aEntity);
    weak_entity addEntity(const std::string & aName, Entity aEntity);

    void removeEntity(weak_entity aEntity);
    void removeEntity(const std::string & aEntityName)
    {   removeEntity(getEntity(aEntityName));   }

    weak_entity getEntity(const std::string & aEntityName)
    {
        return mNamedEntities.left.find(aEntityName)->second;
    }

    /*
     * Families
     */
    template <class T_archetype>
    EntityList & getEntities();

    /// \brief Inteded for downtream use, not used as an internal mechanism
    template <class T_archetype>
    Engine & registerToFamily(FamilyObserver *aObserver);
    template <class T_archetype>
    Engine & cancelFromFamily(FamilyObserver *aObserver);

    /*
     * System
     */
    void addSystem(std::shared_ptr<System> aSystem);

    /*
     * Update
     */
    void update(double aTime);

    /*
     * Callbacks
     */
    void entityCompositionChanged(std::function<void(Family &aFamily)> aFamilyFunctor)
    {
        for (auto &typedFamily : mTypedFamilies)
        {
            aFamilyFunctor(typedFamily.second);
        }
    }

protected:
    void addedEntity(weak_entity aEntity);
    void removedEntity(weak_entity aEntity);

    template <class T_archetype>
    Family & getFamily();

private:
    typedef boost::bimap<std::string, weak_entity > NameEntityMap;
    typedef std::map<ArchetypeTypeId, Family> ArchetypeFamilyMap;

    std::list<LiveEntity> mEntities;
    NameEntityMap mNamedEntities;
    ArchetypeFamilyMap mTypedFamilies;
    std::vector<std::shared_ptr<System>> mSystems;
};

/*
 * Implementations
 */

template <class T_component, class... Args>
LiveEntity & LiveEntity::addComponent(Args&&... aArgs)
{
    mEntity.addComponent(make_component<T_component>(std::forward<Args>(aArgs)...));

    // Note: does not test if insertion actually took place (return value from addComponent())
    //       It is expected to be rare to replace a component this way, so avoid branching
    //       (i.e. always iterate all families, not necessary in the rare replace situation)
    mEngine.entityCompositionChanged([this](Family &family)
    {
       family.componentAddedToEntity(this, type<T_component>());
    });
    return *this;
}

/// \brief Removes the component of type T_component from this Entity.
template <class T_component>
LiveEntity & LiveEntity::removeComponent()
{
    mEngine.entityCompositionChanged([this](Family &family)
    {
      family.componentRemovedFromEntity(this, type<T_component>());
    });
    mEntity.removeComponent<T_component>();
    return *this;
}


template <class T_archetype>
Family & Engine::getFamily()
{
    auto insertionResult = mTypedFamilies.emplace(archetypeTypeId<T_archetype>(),
                                                  T_archetype::gComponentTypes);
    if (insertionResult.second)
    {
        Family &familyRef = insertionResult.first->second;
        for (LiveEntity & wrapper : mEntities)
        {
            familyRef.addIfMatch(entityRefFrom(wrapper));
        }
    }
    return insertionResult.first->second;
}

template <class T_archetype>
EntityList & Engine::getEntities()
{
    return getFamily<T_archetype>().getEntities();
}

template <class T_archetype>
Engine & Engine::registerToFamily(FamilyObserver *aObserver)
{
    getFamily<T_archetype>().registerObserver(aObserver);
    return *this;
}

template <class T_archetype>
Engine & Engine::cancelFromFamily(FamilyObserver *aObserver)
{
    getFamily<T_archetype>().cancelObserver(aObserver);
    return *this;
}

} // namespace aunteater
