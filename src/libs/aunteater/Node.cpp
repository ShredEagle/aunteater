#include "Node.h"

#include "Entity.h"
#include "Engine.h" // for EntityWrapper

using namespace aunteater;


Node::Node(const ArchetypeTypeSet & aIds, weak_entity aAssignedEntity, const family_access &):
    mEntity(aAssignedEntity)
{
    for (ComponentTypeId componentId : aIds)
    {
        mTypedComponents.insert(std::make_pair(componentId, mEntity->get(componentId)));
    }
}

Component & Node::get(ComponentTypeId aComponentId)
{
    return *mTypedComponents.find(aComponentId)->second;
}

const Component & Node::get(ComponentTypeId aComponentId) const
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