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
    return *mTypedComponents.at(aComponentId);
}

const Component & Node::get(ComponentTypeId aComponentId) const
{
    return *mTypedComponents.at(aComponentId);
}
