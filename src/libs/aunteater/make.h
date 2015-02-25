#ifndef _IDG_AE_make
#define _IDG_AE_make

#include "globals.h"

#include <memory>

namespace aunteater
{

    template <class T_component, class... Args>
    own_component<T_component> make_component(Args&&... aArgs)
    {
        // Nota: the actual make method to be called is coupled to own_component underlying type.
        return std::make_unique<T_component>(std::forward<Args>(aArgs)...);
    }

} // namespace aunteater

#endif // #ifdef