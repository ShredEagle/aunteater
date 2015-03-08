#ifndef _IDG_AE_Engine
#define _IDG_AE_Engine

#include "Entity.h"
#include "Family.h"
#include "Handle.h"

#include "globals.h"

#include <boost/bimap.hpp>

#include <map>
#include <string>
#include <vector>

namespace aunteater
{

struct EntityWrapper
{
    EntityWrapper(Entity aEntity, Engine *aEngine) : entity(aEntity)
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
    template <class T_derivedNode>
    std::list<Node> & getNodes();

	/*
	 * System
	 */
	void addSystem(System * System);

	/*
	 * Update
	 */
	void update(float time);

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
    /// \todo make const when there is a distinction between EntityId and EntityRef
    static weak_entity entityIdFrom(EntityWrapper &aWrapper)
    {   return &(aWrapper.entity);  }

    void addedEntity(weak_entity aEntity);
    void removedEntity(weak_entity aEntity);
    
private:
    typedef boost::bimap<std::string, weak_entity > NameEntityMap;
    typedef std::map<ArchetypeTypeId, Family> ArchetypeFamilyMap;

    std::list<EntityWrapper> mEntities;
    NameEntityMap mNamedEntities;
    ArchetypeFamilyMap mTypedFamilies;
	std::vector<System*> mSystems;
};
    
/*
 * Implementations
 */
typedef std::list<Node> & Nodes;

template <class T_nodeArchetype>
std::list<Node> & Engine::getNodes()
{
    // Replace with lazy construction of the Family (emplace, try_emplace ?)
    auto insertionResult = mTypedFamilies.insert(std::make_pair(& typeid(T_nodeArchetype),
                                                 Family(*this, T_nodeArchetype::gComponentTypes)));
    if (insertionResult.second)
    {
        Family &familyRef = insertionResult.first->second;
        for (EntityWrapper & wrapper : mEntities)
        {
            familyRef.testEntityInclusion(entityIdFrom(wrapper));
        }
    }
    return insertionResult.first->second.getNodes();
}
    
} // namespace aunteater

#endif  // #ifdef