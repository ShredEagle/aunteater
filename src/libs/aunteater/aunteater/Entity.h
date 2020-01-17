#pragma once

#include "globals.h"
#include "make.h"

#include <map>

namespace aunteater
{
    class Engine;

    class Entity
    {
    public:

        Entity() = default; // An empty map is exactly what a default Entity needs.

        /*
         * Copy control (based on copy-and-swap idiom: http://stackoverflow.com/a/3279550/1027706)
         */
        Entity(const Entity &aOther);
        //Entity(Entity &&aOther) = default;
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
        /// \brief Adds a component of type T_component, by constructing it forwarding all the provided arguments.
        template <class T_component, class... Args>
        Entity & addComponent(Args&&... aArgs)
        {
            addComponent(make_component<T_component>(std::forward<Args>(aArgs)...));
            return *this;
        }

        /// \brief Removes the component of type T_component from this Entity.
        template <class T_component>
        Entity & removeComponent()
        {
            removeNotifyOwner(type<T_component>());
            mComponents.erase(type<T_component>());
            return *this;
        }

        /// \return true if this Entity has Component of type T_component.
        bool has(ComponentTypeId aId)
        {
            return mComponents.count(aId);
        }

        template <class T_component>
        bool has()
        {
            return mComponents.count(type<T_component>());
        }

        weak_component<> get(ComponentTypeId aId)
        {
            return weakFromOwn(mComponents.find(aId)->second);
        }

        template <class T_component>
        weak_component<T_component> get()
        {
            return static_component_cast<T_component>(mComponents.at(type<T_component>()));
        }

        template <class T_component>
        weak_component<const T_component> get() const
        {
            return static_component_cast<const T_component>(mComponents.at(type<T_component>()));
        }

        /*
         * Engine registration
         */
        Entity &addedToEngine(Engine *aOwner)
        {
            mOwner = aOwner; return *this;
        }

    private:
        void addComponent(own_component<> aComponent);

        /// \brief A wrapper, returning the ComponentTypeId for the provided Component type (T_component)
        template <class T_component>
        static typename std::enable_if_t<std::is_base_of<Component, T_component>::value,
                                         ComponentTypeId>
        type()
        {
            return &typeid(T_component);
        }

        void removeNotifyOwner(ComponentTypeId aComponentId);

    private: // data members
        std::map<ComponentTypeId, own_component<> > mComponents;
        Engine *mOwner = nullptr;
    };


} // namespace aunteater
