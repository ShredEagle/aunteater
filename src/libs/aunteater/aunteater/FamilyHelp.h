#pragma once

#include "Archetype.h"
#include "Engine.h"
#include "Family.h"

namespace aunteater {

    template <class T_archetype>
    class FamilyHelp;

    template <class... VT_components>
    class FamilyHelp<Archetype<VT_components...>>
    {
    public:
        FamilyHelp(Engine & aEngine) :
            mFamily(aEngine.template getFamily<Archetype<VT_components...>>())
        {}

        template <class T_functor>
        void forEach(const T_functor & aOperation) const;

        std::size_t size() const noexcept;

        auto begin() noexcept;
        auto begin() const noexcept;
        auto cbegin() const noexcept;

        auto end() noexcept;
        auto end() const noexcept;
        auto cend() const noexcept;

    private:
        Family & mFamily;
    };

    /***
     * Implementations
     ***/
    template <class... VT_components>
    template <class T_functor>
    void FamilyHelp<Archetype<VT_components...>>::forEach(const T_functor &aOperation) const
    {
        for(auto entity : mFamily)
        {
            aOperation(entity->template get<VT_components>()...);
        }
    }

    template <class... VT_components>
    std::size_t FamilyHelp<Archetype<VT_components...>>::size() const noexcept
    {
        return mFamily.size();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::begin() noexcept
    {
        return mFamily.begin();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::begin() const noexcept
    {
        return mFamily.cbegin();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::cbegin() const noexcept
    {
        return mFamily.cbegin();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::end() noexcept
    {
        return mFamily.end();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::end() const noexcept
    {
        return mFamily.cend();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::cend() const noexcept
    {
        return mFamily.cend();
    }


} // namespace aunteater
