#include "Family.h"

#include "Engine.h"
#include "Entity.h"

#include <algorithm>

using namespace aunteater;

Family::Family(Engine & aEngine, ArchetypeTypeSet aComponentsTypeInfo):
        mEngine(aEngine),
        mComponentsTypeInfo(aComponentsTypeInfo)
{
    
}

void Family::testEntityInclusion(weak_entity aEntity)
{
    addIfMatch(aEntity);
}

void Family::addIfMatch(weak_entity aEntity)
{
    if (std::all_of(mComponentsTypeInfo.begin(), mComponentsTypeInfo.end(),
                    [&aEntity](ComponentTypeId compId){return aEntity->has(compId);}))
    {
        mNodes.emplace_back(mComponentsTypeInfo, aEntity, Node::family_access());
        /*auto insertionResult = */ mEntitiesToNodes.emplace(aEntity, --mNodes.end());
        /// \todo Do we need to test if the handle was already present ?
    }
}

void Family::removeIfPresent(entity_id aEntity)
{
    auto foundIt = mEntitiesToNodes.find(aEntity);
    if (foundIt != mEntitiesToNodes.end())
    {
        mNodes.erase(foundIt->second);
        mEntitiesToNodes.erase(foundIt);
    }
}

void Family::componentAddedToEntity(weak_entity aEntity, ComponentTypeId aComponent)
{
    if(!isPresent(aEntity))
    {
        addIfMatch(aEntity);
    }
}

void Family::componentRemovedFromEntity(entity_id aEntity, ComponentTypeId aComponent)
{
    if (includesComponent(aComponent))
    {
        removeIfPresent(aEntity);
    }
}

bool Family::isPresent(entity_id aEntity) const
{
    return mEntitiesToNodes.find(aEntity) != mEntitiesToNodes.end();
}

bool Family::includesComponent(ComponentTypeId aComponent) const
{
    return mComponentsTypeInfo.count(aComponent);
}

//void Family::componentAddedToEntity(std::shared_ptr<Entity> aEntity, ComponentTypeId aComponent);
//void Family::componentRemovedFromEntity(std::shared_ptr<Entity> aEntity, ComponentTypeId aComponent);
/*
void Family::removeEntity(std::shared_ptr<Entity> aEntity)
{
    removeIfMatch(aEntity);
}

void Family::componentAddedToEntity(std::shared_ptr<Entity> aEntity, <#std::type_info *aComponent#>)
{
    
}
*/