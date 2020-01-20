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
    operator Entity()
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
    weak_component<T_component> get()
    {
        return mEntity.get<T_component>();
    }

    /// TODO remove!
    weak_component<> get(ComponentTypeId aId)
    {
        return mEntity.get(aId);
    }

    template <class T_component>
    weak_component<const T_component> get() const
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
    std::list<Node> & getNodes();

    // NOTE: For users, not used as an internal mechanism
    template <class T_archetype>
    Engine & registerToNodes(FamilyObserver *aObserver);

    template <class T_archetype>
    Engine & cancelFromNodes(FamilyObserver *aObserver);

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
        //std::for_each(mTypedFamilies.begin(), mTypedFamilies.end(), aFamilyFunctor); // would require some boost adaptor to take the mapped_type
        for (auto &typedFamily : mTypedFamilies)
        {
            aFamilyFunctor(typedFamily.second);
        }
    }
protected:
    static entity_id entityIdFrom(const LiveEntity &aWrapper)
    {
        return &aWrapper;
    }

    static weak_entity entityRefFrom(LiveEntity &aWrapper)
    {
        return &aWrapper;
    }

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
    if(mEntity.addComponent(make_component<T_component>(std::forward<Args>(aArgs)...)))
    {
        mEngine.entityCompositionChanged([this](Family &family)
        {
           family.componentAddedToEntity(this, type<T_component>());
        });
    }
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


typedef std::list<Node> * Nodes;

template <class T_archetype>
Family & Engine::getFamily()
{
    auto insertionResult = mTypedFamilies.emplace(archetypeTypeId<T_archetype>(),
                                                  Family(T_archetype::gComponentTypes));
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
std::list<Node> & Engine::getNodes()
{
    return getFamily<T_archetype>().getNodes();
}

template <class T_archetype>
Engine & Engine::registerToNodes(FamilyObserver *aObserver)
{
    getFamily<T_archetype>().registerObserver(aObserver);
    return *this;
}

template <class T_archetype>
Engine & Engine::cancelFromNodes(FamilyObserver *aObserver)
{
    getFamily<T_archetype>().cancelObserver(aObserver);
    return *this;
}

} // namespace aunteater
