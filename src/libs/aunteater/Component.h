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
        
		virtual const std::type_info & getTypeInfo() =0;
    };
    
} // namespace aunteater

#endif  // #ifdef