#pragma once

#include "globals.h"

#include <map>

namespace aunteater
{

    struct EntityWrapper;
    class Family;

    // Review note: this seems like a glorified wrapper around an entity weak pointer
    // could probably do without, as it seems not to offer any service
    // by simply holding reference to the right subset of components.
    class Node
    {
    public:
        class family_access
        {
            friend class Family;

            family_access() = default;
            family_access(const family_access &) = delete;
            family_access & operator=(const family_access &) = delete;
        };

        weak_entity getEntity()
        {
            return mEntity;
        }

    public:
        explicit Node(const ArchetypeTypeSet & aIds, weak_entity aAssignedEntity, const family_access &);

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
        Component & get(ComponentTypeId aComponentId);
        const Component & get(ComponentTypeId aComponentId) const;

    private:
        /// \todo Same as with Entity::get() : it would be nice to avoir sharing ownership.
        /// In the end, we probably want a better Handler type, and use Handler and Components
        std::map<ComponentTypeId, weak_component<> > mTypedComponents;
        weak_entity mEntity;

    };

} // namespace aunteater
