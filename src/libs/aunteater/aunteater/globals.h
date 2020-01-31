#pragma once

#include <memory>
#include <set>
#include <typeinfo>

namespace aunteater
{
    class Component;
    class LiveEntity;
    class System;

    typedef const std::type_info * ComponentTypeId;


    /// \brief Returns the ComponentTypeId for the provided Component type (T_component)
    template <class T_component>
    static typename std::enable_if_t<std::is_base_of<Component, T_component>::value,
                                     ComponentTypeId>
    type()
    {
        return &typeid(T_component);
    }

    /// \todo We do not want to share ownership : Entity is semantically owning its components,
    /// other objects are refering to them.
    template <class T_component = Component>
    using own_component = std::unique_ptr<T_component>;

    typedef std::set<ComponentTypeId> ArchetypeTypeSet;

    typedef const std::type_info *  ArchetypeTypeId;
    template <class T_Archetype>
    constexpr ArchetypeTypeId archetypeTypeId()
    {
        return & typeid(T_Archetype);
    }

    typedef const LiveEntity* entity_id; // Could alternatively be a const void*: should never be used to invoke methods.
    typedef LiveEntity* weak_entity;

    inline entity_id entityIdFrom(const LiveEntity &aWrapper)
    {
        return &aWrapper;
    }

    inline weak_entity entityRefFrom(LiveEntity &aWrapper)
    {
        return &aWrapper;
    }

} // namespace aunteater
