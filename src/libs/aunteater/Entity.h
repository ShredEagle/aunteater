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

        Entity() = default; // An empty map is exactly what a default Entity needs.

        /*
         * Copy control (based on copy-and-swap idiom: http://stackoverflow.com/a/3279550/1027706)
         */
        Entity(const Entity &aOther);
        Entity(Entity &&aOther) = default;
        Entity & operator=(Entity aRhs);  //take the argument by value, following copy-and-swap idiom.
        //Entity & operator=(Entity &&aRhs) = default; //the potential advantage of such declaration is small (at best)
            //if it was not there, the move assignment would be disabled, falling back to copy assignment
            //which would be calling the move-ctor (argument being an rvalue) and then swapping.
            // In fact, it introduces a call ambiguity when operator= is invoked on an rvalue.

        // Nota: no need for custom deletion, it is correctly handled by the smart pointer.
        // yet, since we have a unique_ptr in the data members, and the pointed type is only fully defined in the .cpp
        // this class dtor should be defined in the .cpp.
        ~Entity();

        friend void swap(Entity &aLhs, Entity &aRhs)
        {
            using std::swap; //enables ADL, offers no benefits in the case of swaping the map.
            swap(aLhs.mComponents, aRhs.mComponents);
        }

        /*
         * Components management
         */
        /// \brief Adds a component
        /// \deprecated Use template addComponent instead
        void addComponent(own_component<> aComponent);

        /// \todo MAJOR for add and remove component, update the families !

        /// \brief Adds a component of type T_component, by constructing it forwarding all the provided arguments.
        template <class T_component, class... Args>
        Entity & addComponent(Args&&... aArgs)
        {   addComponent(make_component<T_component>(std::forward<Args>(aArgs)...)); return *this;    }

        // Nota: Is not inlined, because unique_ptr<Component> are erased by this impl, and Component is incomplete.
        /// \deprecated
        Entity & removeComponent(ComponentTypeId aComponentId);

        /// \brief Removes the component of type T_component from this Entity.
        template <class T_component>
        Entity & removeComponent()
        {   mComponents.erase(type<T_component>()); return *this;   }

        /// \deprecated
        bool has(ComponentTypeId aComponentId)
        {   return mComponents.count(aComponentId); }

        /// \return true if this Entity has Component of type T_component.
        template <class T_component>
        bool has()
        {   return mComponents.count(type<T_component>());    }

        /// \note Undefined behavior if aComponentId is not a key in the map.
        /// \deprecated Use template get() instead.
        weak_component<> get(ComponentTypeId aComponentId)
        {   return weakFromOwn(mComponents.find(aComponentId)->second);  }

        /// \note It is an undefined behavior to call this if T_component is not a component of the Entity.
        template <class T_component>
        weak_component<T_component> get()
        {   return static_component_cast<T_component>(mComponents.find(type<T_component>())->second);   }

    private:
        /// \brief A wrapper, returning the ComponentTypeId for the provided Component type (T_component)
        template <class T_component>
        static constexpr typename std::enable_if<std::is_base_of<Component, T_component>::value, ComponentTypeId>::type
        type()
        {   return &typeid(T_component);    }

    private:
        std::map<ComponentTypeId, own_component<> > mComponents;
    };
    
} // namespace aunteater

#endif  // #ifdef