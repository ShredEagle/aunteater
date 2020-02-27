#pragma once

#include "globals.h"


namespace aunteater {

typedef std::set<ComponentTypeId> ArchetypeTypeSet;

template <class... VT_components>
struct Archetype
{
    static ArchetypeTypeSet TypeSet()
    {
        return {type<VT_components>()...};
    }
};

template <class T_archetype>
class Archetype_size;

template <class... VT_components>
class Archetype_size<Archetype<VT_components...>> :
    public std::integral_constant<std::size_t, sizeof...(VT_components)>
{};

template <std::size_t I, class T_archetype>
class Archetype_element;

template <std::size_t I, class... VT_components>
class Archetype_element<I, Archetype<VT_components...>> :
    public std::tuple_element<I, std::tuple<VT_components...>>
{};

} // namespace aunteater
