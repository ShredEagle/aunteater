#ifndef _IDG_AE_Node
#define _IDG_AE_Node

#include "Component.h"
#include <set>
#include <typeinfo>
#include <map>

namespace aunteater
{

class Node
{
private:
    std::map<std::type_info *, Component> mComponents;
public:
    std::set<std::type_info * > getComponentsTypeInfo();
};
    
} // namespace aunteater

#endif  // #ifdef