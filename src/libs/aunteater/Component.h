#ifndef _IDG_AE_Component
#define _IDG_AE_Component

#include "globals.h"

#include "make.h"

namespace aunteater
{
    
    class Component
    {
    public:
        // Component class needs to be polymorphic to enable RTTI.
        virtual ~Component()
        {}
        
        /// \todo Rename to loosen the logical coupling to type_info (eg. getType())
		ComponentTypeId getTypeInfo()
        {
            return &typeid(*this);
        }
    };

} // namespace aunteater

#endif  // #ifdef