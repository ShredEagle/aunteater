#include "Node.h"

using namespace aunteater;

std::set<std::type_info * > Node::getComponentsTypeInfo()
{
    std::set<std::type_info * > typeInfoSet;
    for(auto pair : mComponents)
    {
        typeInfoSet.insert(pair.first);
    }
    
    return typeInfoSet;
}