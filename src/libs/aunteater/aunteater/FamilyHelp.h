#pragma once

#include "Archetype.h"
#include "Engine.h"
#include "Family.h"

// TODO remove
#include <iostream>

namespace aunteater {


    template <class T_iterator, class T_archetype>
    class EntityWrap;

    template <class T_iterator, class... VT_components>
    class EntityWrap<T_iterator, Archetype<VT_components...>>
    {
        template <class>
        friend class FamilyHelp;

        typedef T_iterator iterator;

        EntityWrap(iterator aIterator) :
            mEntity(aIterator)
        {}

    public:

        weak_entity operator->()
        {
            return *mEntity;
        }

        // Part of structured binding implementation
        template <std::size_t I>
        auto & get() &
        {
            return (*mEntity)->template get<typename std::tuple_element<I, EntityWrap>::type>();
        }

        template <std::size_t I>
        auto get() &&
        {
            return (*mEntity)->template get<typename std::tuple_element<I, EntityWrap>::type>();
        }

        template <std::size_t I>
        auto & get() const &
        {
            return (*mEntity)->template get<typename std::tuple_element<I, EntityWrap>::type>();
        }

        template <std::size_t I>
        auto get() const &&
        {
            return (*mEntity)->template get<typename std::tuple_element<I, EntityWrap>::type>();
        }

        // Note: This operator has to behave in a surprising manner:
        //  It will be used by the range-base for loop, assigning its result
        //  to the "range_declaration".
        //  If it behaved in a normal manner (returning the pointed to object, i.e. weak_entity),
        //  it would lose all benefits from wrapping
        //  (i.e. structured binding and statically checked get)
        EntityWrap & operator*()
        {
            return *this;
        }

        auto operator==(const EntityWrap & aOther) const
        {
            return mEntity == aOther.mEntity;
        }

        auto operator!=(const EntityWrap & aOther) const
        {
            return mEntity != aOther.mEntity;
        }

        EntityWrap & operator++()
        {
            ++mEntity;
            return *this;
        }

        EntityWrap operator++(int)
        {
            return mEntity++;
        }

    private:
         iterator mEntity;
    };


    template <class T_archetype>
    class FamilyHelp;

    template <class... VT_components>
    class FamilyHelp<Archetype<VT_components...>>
    {
    public:
        using Wrap = EntityWrap<decltype(std::declval<Family>().begin()),
                                Archetype<VT_components...>>;
        using const_Wrap = EntityWrap<decltype(std::declval<Family>().cbegin()),
                                      Archetype<VT_components...>>;

        FamilyHelp(Engine & aEngine) :
            mFamily(aEngine.template getFamily<Archetype<VT_components...>>())
        {}

        template <class T_functor>
        void forEach(const T_functor & aOperation) const;

        std::size_t size() const noexcept;

        Wrap begin() noexcept;
        const_Wrap begin() const noexcept;
        const_Wrap cbegin() const noexcept;

        Wrap end() noexcept;
        const_Wrap end() const noexcept;
        const_Wrap cend() const noexcept;

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
    auto FamilyHelp<Archetype<VT_components...>>::begin() noexcept -> Wrap
    {
        return mFamily.begin();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::begin() const noexcept -> const_Wrap
    {
        return mFamily.cbegin();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::cbegin() const noexcept -> const_Wrap
    {
        return mFamily.cbegin();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::end() noexcept -> Wrap
    {
        return mFamily.end();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::end() const noexcept -> const_Wrap
    {
        return mFamily.cend();
    }

    template <class... VT_components>
    auto FamilyHelp<Archetype<VT_components...>>::cend() const noexcept -> const_Wrap
    {
        return mFamily.cend();
    }


} // namespace aunteater

//
// Structured binding implementation
//
namespace std {

template <class T_iterator, class T_archetype>
class tuple_size<aunteater::EntityWrap<T_iterator, T_archetype>> :
    public std::integral_constant<size_t, aunteater::Archetype_size<T_archetype>::value>
{};

template <std::size_t I, class T_iterator, class T_archetype>
class tuple_element<I, aunteater::EntityWrap<T_iterator, T_archetype>> :
    public aunteater::Archetype_element<I, T_archetype>
{};

} // namespace std
