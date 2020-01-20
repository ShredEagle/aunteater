#pragma once

#include "globals.h"
#include "make.h"

#include <map>

namespace aunteater
{
    class Engine;

    /// \brief Entity class
    class Entity
    {
        friend class LiveEntity;

    public:
        Entity() = default; // An empty map is exactly what a default Entity needs.

        /*
         * Copy and move control
         * (based on copy-and-swap idiom: http://stackoverflow.com/a/3279550/1027706)
         */
        Entity(const Entity &aOther);
        Entity(Entity &&aOther);
        Entity & operator=(Entity aRhs);  //take the argument by value, following copy-and-swap idiom.

        // To be default implemented in the .cpp because unique_ptr to incomplete type
        ~Entity();

        void swap(Entity &aLhs, Entity &aRhs)
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

    private:
        bool addComponent(own_component<> aComponent);

    private: // data members
        std::map<ComponentTypeId, own_component<> > mComponents;
    };

} // namespace aunteater
