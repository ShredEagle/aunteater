#ifndef _IDG_AE_Component
#define _IDG_AE_Component

#include <typeinfo>

namespace aunteater
{
    
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