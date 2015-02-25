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
        typedef std::map<ArchetypeTypeId, Family> ArchetypeFamilyMap;
        
        std::vector<Entity> mEntities;
        NameEntityMap mNamedEntities;
        ArchetypeFamilyMap mTypedFamilies;
		std::vector<System*> mSystems;
    };
    
    
    typedef std::list<Node> & Nodes;
    
    template <class T_nodeArchetype>
    std::list<Node> & Engine::getNodes()
    {
        // Replace with lazy construction of the Family (emplace, try_emplace ?)
        auto insertionResult =
            mTypedFamilies.insert(std::make_pair(& typeid(T_nodeArchetype),
                                                 Family(*this, T_nodeArchetype::gComponentTypes)));
        if (insertionResult.second)
        {
            Family &familyRef = insertionResult.first->second;
//            for (Entity & entity : mEntities)
            for (std::vector<Entity>::size_type index = 0;
                 index != mEntities.size();
                 ++index)
            {
                familyRef.testEntityInclusion(Handle<Entity>(mEntities, index));
            }
        }
        return insertionResult.first->second.getNodes();
    }
    
} // namespace aunteater

#endif  // #ifdef