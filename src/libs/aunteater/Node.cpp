#include "Node.h"

#include "Entity.h"

using namespace aunteater;



Node::Node(const ComponentIds & aIds, Handle<Entity> aAssignedEntity, const family_access &):
    mEntity(aAssignedEntity)
{
    for (ComponentId componentId : aIds)
    {
        mTypedComponents.insert(std::make_pair(componentId, aAssignedEntity->get(componentId)));
    }
}

Component & Node::get(const std::type_info *aComponentId)
{
    return *mTypedComponents.find(aComponentId)->second;
}

/*
std::set<std::type_info * > Node::getComponentsTypeInfo()
{
    std::set<std::type_info * > typeInfoSet;
    for(auto pair : mComponents)
    {
        typeInfoSet.insert(pair.first);
    }
    
    return typeInfoSet;
}
*/