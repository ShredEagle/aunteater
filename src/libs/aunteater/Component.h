#ifndef _IDG_AE_Component
#define _IDG_AE_Component

#include <set>
#include <typeinfo>

namespace aunteater
{
    
    typedef const std::type_info * ComponentTypeId;
    typedef std::set<ComponentTypeId> ArchetypeTypeSet;

    class Component
    {
    public:
        // Component class needs to be polymorphic to enable RTTI.
        virtual ~Component()
        {}
        
        /// \todo Rename to loosen the logical coupling to type_info (eg. getType())
		const std::type_info * getTypeInfo()
        {
            return &typeid(*this);
        }
    };
    
} // namespace aunteater

#endif  // #ifdef