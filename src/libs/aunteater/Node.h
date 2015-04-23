#ifndef _IDG_AE_Node
#define _IDG_AE_Node

#include "Handle.h"

#include "globals.h"

#include <map>

namespace aunteater
{

    class EntityWrapper;
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
        
        weak_entity getEntity()
        {
            return mEntity;
        }
        
    public:
        explicit Node(const ArchetypeTypeSet & aIds, weak_entity aAssignedEntity, const family_access &);
        
        /// It is an undefined behavior to give a ComponentId that is not present in the collection
        /// \deprecated
        Component & get(ComponentTypeId aComponentId);
        const Component & get(ComponentTypeId aComponentId) const;

        template <class T_component>
        T_component & get()
        {
            return static_cast<T_component &>(get(&typeid(T_component)));
        }

        template <class T_component>
        const T_component & get() const
        {
            return static_cast<const T_component &>(get(&typeid(T_component)));
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
        weak_entity mEntity;
        
    };
    
} // namespace aunteater

#endif  // #ifdef
