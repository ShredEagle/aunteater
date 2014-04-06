#ifndef _IDG_AE_Node
#define _IDG_AE_Node

#include "Component.h"
#include <set>
#include <typeinfo>
#include <map>
#include <memory>

namespace aunteater
{

    class Entity;
    class Family;
    
    typedef std::set<const std::type_info *> ComponentIds;
    
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
        
    public:
        explicit Node(const ComponentIds & aIds, Entity & aAssignedEntity, const family_access &);
        
        /// It is an undefined behavior to give a ComponentId that is not present in the collection
        Component & get(const std::type_info *aComponentId);
        
        template <class T_component>
        T_component & get()
        {
            return static_cast<T_component &>(get(&typeid(T_component)));
        }
        
        //std::set<std::type_info * > getComponentsTypeInfo();
        
    private:
        /// \todo Same as with Entity::get() : it would be nice to avoir sharing ownership.
        /// In the end, we probably want a better Handler type, and use Handler and Components
        std::map<const std::type_info *, std::shared_ptr<Component>> mTypedComponents;
        
    };
    
} // namespace aunteater

#endif  // #ifdef