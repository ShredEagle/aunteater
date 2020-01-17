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

struct EntityWrapper
{
    EntityWrapper(Entity aEntity, Engine *aEngine) :
        entity(std::move(aEntity))
    {
        entity.addedToEngine(aEngine);
        //engine->addedEntity(&entity); //dangerous, if the EntityWrapper is moved the address moves along...
    }

    EntityWrapper(const EntityWrapper&) = delete;
    EntityWrapper & operator=(const EntityWrapper&) = delete;

    ~EntityWrapper()
    {
        //engine.removedEntity(&entity)
        entity.addedToEngine(nullptr);
    }

    //operator Entity&() /// Interestingly, that syntax seems to do exactly what you'd expect ; )
    //{
    //    return entity;
    //}

    Entity entity;
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
    template <class T_nodeArchetype>
    std::list<Node> & getNodes();

    template <class T_nodeArchetype>
    Engine & registerToNodes(FamilyObserver *aObserver);

    template <class T_nodeArchetype>
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
    static entity_id entityIdFrom(const EntityWrapper &aWrapper)
    {   return &(aWrapper.entity);  }

    static weak_entity entityRefFrom( EntityWrapper &aWrapper)
    {   return &(aWrapper.entity);  }

    void addedEntity(weak_entity aEntity);
    void removedEntity(weak_entity aEntity);

    template <class T_nodeArchetype>
    Family & getFamily();

private:
    typedef boost::bimap<std::string, weak_entity > NameEntityMap;
    typedef std::map<ArchetypeTypeId, Family> ArchetypeFamilyMap;

    std::list<EntityWrapper> mEntities;
    NameEntityMap mNamedEntities;
    ArchetypeFamilyMap mTypedFamilies;
    std::vector<std::shared_ptr<System>> mSystems;
};

/*
 * Implementations
 */
typedef std::list<Node> * Nodes;

template <class T_nodeArchetype>
Family & Engine::getFamily()
{
    // Replace with lazy construction of the Family (emplace, try_emplace ?)
    auto insertionResult = mTypedFamilies.insert(std::make_pair(& typeid(T_nodeArchetype),
                                                 Family(*this, T_nodeArchetype::gComponentTypes)));
    if (insertionResult.second)
    {
        Family &familyRef = insertionResult.first->second;
        for (EntityWrapper & wrapper : mEntities)
        {
            familyRef.testEntityInclusion(entityRefFrom(wrapper));
        }
    }
    return insertionResult.first->second;
}

template <class T_nodeArchetype>
std::list<Node> & Engine::getNodes()
{
    return getFamily<T_nodeArchetype>().getNodes();
}

template <class T_nodeArchetype>
Engine & Engine::registerToNodes(FamilyObserver *aObserver)
{
    getFamily<T_nodeArchetype>().registerObserver(aObserver);
    return *this;
}

template <class T_nodeArchetype>
Engine & Engine::cancelFromNodes(FamilyObserver *aObserver)
{
    getFamily<T_nodeArchetype>().cancelObserver(aObserver);
    return *this;
}

} // namespace aunteater
