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

} // namespace aunteater
