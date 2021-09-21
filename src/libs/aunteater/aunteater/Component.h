#pragma once

#include "globals.h"

#include "make.h"


namespace aunteater
{

    class ComponentBase
    {
        friend own_component<> clone(const own_component<> &aComponent);

    public:
        // Component class needs to be polymorphic to enable RTTI.
        virtual ~ComponentBase()
        {}

        /// \todo Rename to loosen the logical coupling to type_info (eg. getType())
        ComponentTypeId getTypeInfo()
        {
            return &typeid(*this);
        }

    private:
        virtual own_component<> clone_impl() const = 0;
    };


    template <class T_derived>
    class Component : public ComponentBase
    {
    private:
        own_component<> clone_impl() const final
        {
            return std::make_unique<T_derived>(*static_cast<const T_derived*>(this));
        }
    };


    /// \brief This method is to be used when client code needs a copy of a component through a pointer to the base.
    /// \note It is implemented this way to isolate the rest of the code from the actual implementation of the
    /// dynamic-type dependent call. It is not sure we want to keep a virtual clone method in Component.
    inline own_component<> clone(const own_component<> &aComponent)
    {
        return aComponent->clone_impl();
    }

} // namespace aunteater
