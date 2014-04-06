#ifndef _IDG_AE_Engine
#define _IDG_AE_Engine

#include "Entity.h"
#include "Family.h"
#include "Handle.h"

#include <boost/bimap.hpp>

#include <map>
#include <string>
#include <typeinfo>
#include <vector>

namespace aunteater
{
	class System;

    class Engine
    {
    public:
        /*
         * Entities manipulation
         */
        Handle<Entity> addEntity(Entity aEntity);
        Handle<Entity> addEntity(const std::string & aName, Entity aEntity);
        
        void removeEntity(Handle<Entity> aId);
        
        Handle<Entity> getEntity(const std::string & aName)
        {
            return mNamedEntities.left.find(aName)->second;
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
        
    protected:
        void addedEntity(Handle<Entity> aEntity);
        void removedEntity(Handle<Entity> aEntity);
        
    private:
        typedef boost::bimap<std::string, Handle<Entity> > NameEntityMap;
        typedef std::map<const std::type_info *, Family> ArchetypeFamilyMap;
        
        std::vector<Entity> mEntities;
        NameEntityMap mNamedEntities;
        ArchetypeFamilyMap mTypedFamilies;
		std::vector<System*> mSystems;
    };
    
    
    typedef std::list<Node> & Nodes;
    
    template <class T_nodeArchetype>
    std::list<Node> & Engine::getNodes()
    {
        auto insertionResult =
            mTypedFamilies.insert(std::make_pair(& typeid(T_nodeArchetype),
                                                 Family(*this, T_nodeArchetype::gComponentTypes)));
        if (insertionResult.second)
        {
            Family &familyRef = insertionResult.first->second;
            for (Entity & entity : mEntities)
            {
                familyRef.testEntityInclusion(entity);
            }
        }
        return insertionResult.first->second.getNodes();
    }
    
} // namespace aunteater

#endif  // #ifdef