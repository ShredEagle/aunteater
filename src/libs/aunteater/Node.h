#ifndef _IDG_AE_Node
#define _IDG_AE_Node

#include "Handle.h"

#include "globals.h"

#include <map>

namespace aunteater
{

    class Entity;
    class Family;
    
    class Node
    {
    public:
        class family_access
        {
            friend class Family;
            
            family_access() {};
            family_access(const family_access &) = delete;
            family_access & operator=(const family_access &) = delete;
        };
        
        Handle<Entity> getEntity()
        {
            return mEntity;
        }
        
    public:
        explicit Node(const ArchetypeTypeSet & aIds, Handle<Entity> aAssignedEntity, const family_access &);
        
        /// It is an undefined behavior to give a ComponentId that is not present in the collection
        /// \deprecated
        Component & get(ComponentTypeId aComponentId);
        
        template <class T_component>
        T_component & get()
        {
            return static_cast<T_component &>(get(&typeid(T_component)));
        }
        
        bool operator==(const Node &aRhs) const
        {
            return (mTypedComponents == aRhs.mTypedComponents) && (mEntity == aRhs.mEntity);
        }
        
        bool operator!=(const Node &aRhs) const
        {
            return !(*this == aRhs);
        }
        
    private:
        /// \todo Same as with Entity::get() : it would be nice to avoir sharing ownership.
        /// In the end, we probably want a better Handler type, and use Handler and Components
        std::map<ComponentTypeId, weak_component<> > mTypedComponents;
        Handle<Entity> mEntity;
        
    };
    
} // namespace aunteater

#endif  // #ifdef
