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
    LiveEntity & add(Args&&... aArgs);

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

    void markToRemove(weak_entity aEntity)
    {
        mEntitiesToRemove.emplace(aEntity);
    }
    void markToRemove(const std::string & aEntityName)
    {
        markToRemove(getEntity(aEntityName));
    }

    weak_entity getEntity(const std::string & aEntityName)
    {
        return mNamedEntities.left.find(aEntityName)->second;
    }

    /*
     * Families
     */
    template <class T_archetype>
    Family & getFamily();

    /*
     * System
     */
    /// \brief Instantiate and add a system of class T_system.
    ///
    ///  Provides engine reference as 1st ctor argument, forwards aArgs as following arguments.
    template <class T_system, class... VT_ctorArgs>
    void addSystem(VT_ctorArgs &&... aArgs);

    void addSystem(std::shared_ptr<System> aSystem);

    /*
     * Update
     */
    template <class T_updater>
    void update(double time, T_updater && aUpdater);

    void update(double aTime);

    void forEachFamily(std::function<void(Family &aFamily)> aFamilyFunctor)
    {
        for (auto &typedFamily : mTypedFamilies)
        {
            aFamilyFunctor(typedFamily.second);
        }
    }

protected:
    void removeEntities();
    void notifyAdditionToFamilies(weak_entity aEntity);
    void notifyRemovalToFamilies(entity_id aEntity);

private:
    typedef boost::bimap<std::string, weak_entity > NameEntityMap;
    typedef std::map<ArchetypeTypeId, Family> ArchetypeFamilyMap;

    std::list<LiveEntity> mEntities;
    NameEntityMap mNamedEntities;
    std::set<weak_entity> mEntitiesToRemove;
    ArchetypeFamilyMap mTypedFamilies;

protected:
    std::vector<std::shared_ptr<System>> mSystems;
};

/*
 * Implementations
 */

template <class T_component, class... Args>
LiveEntity & LiveEntity::add(Args&&... aArgs)
{
    mEntity.add<T_component>(std::forward<Args>(aArgs)...);

    // Note: does not test if insertion actually took place (return value from addComponent())
    //       It is expected to be rare to replace a component this way, so avoid branching
    //       (i.e. always iterate all families, not necessary in the rare replace situation)
    mEngine.forEachFamily([this](Family &family)
    {
       family.componentAddedToEntity(this, type<T_component>());
    });
    return *this;
}

/// \brief Removes the component of type T_component from this Entity.
template <class T_component>
LiveEntity & LiveEntity::removeComponent()
{
    mEngine.forEachFamily([this](Family &family)
    {
      family.componentRemovedFromEntity(entityIdFrom(*this), type<T_component>());
    });
    mEntity.remove<T_component>();
    return *this;
}

template <class T_system, class... VT_ctorArgs>
void Engine::addSystem(VT_ctorArgs &&... aArgs)
{
    addSystem(std::make_shared<T_system>(*this, std::forward<VT_ctorArgs>(aArgs)...));
}

template <class T_archetype>
Family & Engine::getFamily()
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

template <class T_updater>
void Engine::update(double time, T_updater && aUpdater)
{
    aUpdater.start();

    for (auto & system : mSystems)
    {
        aUpdater(*system, time);
    }
    removeEntities();

    aUpdater.finish();
}

} // namespace aunteater
