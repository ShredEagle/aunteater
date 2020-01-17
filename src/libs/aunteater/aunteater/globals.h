#pragma once

#include <memory>
#include <set>
#include <typeinfo>

namespace aunteater
{
    class Entity;
    class Component;
    class System;

    typedef const std::type_info * ComponentTypeId;

    /// \todo We do not want to share ownership : Entity is semantically owning its components,
    /// other objects are refering to them.
    template <class T_component = Component>
//    using own_component = std::shared_ptr<T_component>;
    using own_component = std::unique_ptr<T_component>;
    template <class T_component = Component>
//    using weak_component = std::shared_ptr<T_component>;
    using weak_component = T_component*;

    template <class T_component = Component>
    weak_component<T_component> weakFromOwn(const own_component<> &aOwnComponent)
    {
//        return aOwnComponent;
        return aOwnComponent.get();
    }

    template <class T_destComponent, class T_sourceComponent>
    weak_component<T_destComponent> static_component_cast(const own_component<T_sourceComponent> &aOwnComponent)
    {
        //return std::static_pointer_cast<T_destComponent>(aOwnComponent);
        return static_cast<weak_component<T_destComponent>>(weakFromOwn(aOwnComponent));
    }

    typedef std::set<ComponentTypeId> ArchetypeTypeSet;
    typedef const std::type_info *  ArchetypeTypeId;

    typedef const Entity* entity_id; // Could alternatively be a const void*: should never be used to invoke methods.
    typedef Entity* weak_entity;

} // namespace aunteater
