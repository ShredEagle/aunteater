#ifndef _IDG_AE_Component
#define _IDG_AE_Component

#include <set>
#include <typeinfo>

namespace aunteater
{
    
    typedef const std::type_info * ComponentId;
    
    class Component
    {
    public:
        
        const std::type_info & getTypeInfo()
        {
            return typeid(*this);
        }
    };
    
} // namespace aunteater

#endif  // #ifdef