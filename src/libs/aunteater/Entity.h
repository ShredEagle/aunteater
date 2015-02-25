#ifndef _IDG_AE_Entity
#define _IDG_AE_Entity

#include "globals.h"
#include "make.h"

#include <map>

namespace aunteater
{

    class Entity
    {
    public:
        /// \brief Adds a component
        /// \deprecated Use template addComponent instead
        void addComponent(own_component<> aComponent);

        /// \todo MAJOR for add and remove component, update the families !
        
        template <class T_component, class... Args>
        Entity & addComponent(Args&&... aArgs)
        {   addComponent(make_component<T_component>(std::forward<Args>(aArgs)...)); return *this;    }

        Entity & removeComponent(ComponentTypeId aComponentId)
        {   mComponents.erase(aComponentId); return *this;  }
        
        bool has(ComponentTypeId aComponentId)
        {   return mComponents.count(aComponentId); }

        /// Undefined behavior if aComponentId is not a key in the map.
        /// \deprecated Use template get() instead.
        weak_component<> get(ComponentTypeId aComponentId)
        {   return weakFromOwn(mComponents.find(aComponentId)->second);  }

        /// \note It is an undefined behavior to call this if T_component is not a component of the Entity.
        template <class T_component>
        weak_component<T_component> get()
        {
            return std::static_pointer_cast<T_component>
                (mComponents.find(&typeid(T_component))->second);
        }
        
    private:
        std::map<ComponentTypeId, own_component<> > mComponents;
    };
    
} // namespace aunteater

#endif  // #ifdef