#ifndef _IDG_AE_globals
#define _IDG_AE_globals

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
    using own_component = std::shared_ptr<T_component>;
//    using own_component = std::unique_ptr<T_component>;
    template <class T_component = Component>
    using weak_component = std::shared_ptr<T_component>;
//    using weak_component = T_component*;

    template <class T_component = Component>
    weak_component<T_component> weakFromOwn(const own_component<> &aOwnComponent)
    {
        return aOwnComponent;
//        return aOwnComponent.get();
    }

    typedef std::set<ComponentTypeId> ArchetypeTypeSet;
    typedef const std::type_info *  ArchetypeTypeId;


} // namespace aunteater
#endif  // #ifdef